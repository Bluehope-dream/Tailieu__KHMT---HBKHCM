#include "UnitList.h"
// Hàm kiểm tra số đặc biệt 
bool UnitList:: isSpecialNum(int val, int n){
    if (val <=0 || n<=1 ) return false;
    while (val >0){
        int tempo = val %  n;
        if (tempo == 0){
            val/=n;
        } else if (tempo==1) {
            val--;
        }
        else return false;  // Có chữ số lớn hơn 1 ko hợp lệ 
    }
    return true;
}
bool UnitList::checkSpecialNumber(int val){  // Có thể Sử dụng thuật toán vét cạn backTracking để tính toán 
    if (val<=0) return false;
    const int base [] = {3,5,7};  // Xác định cơ số nó là một số nguyên tố lẻ nhỏ hơn 10
    for (int i: base){
        if (isSpecialNum(val,i)) return true;
    }
    return false;
}
// 
UnitList::UnitList(int S) : head(nullptr),tail(nullptr),countInfantry(0), countVehicle(0), currSize (0)
{
    // TODO: Implement
    // Xét S để dưa ra chỉ số nếu S là special Num thì capacity = 12, còn ko nó chính là 8 
    if (checkSpecialNumber(S)) {
        capacity = 12;
    }
    else{
        capacity = 8;
    } 
}
// Giai phóng thủ công vùng nhớ đc cập phát giải phóng thủ công bằng tay
UnitList:: ~UnitList (){
    clear();
}
void UnitList::clear (){
    Node * current = head;
    while (current != nullptr){
        Node* tempo = current;
        current  = current  -> next;
        delete tempo -> unit;
        delete tempo;
    }
    head = nullptr;
    tail = nullptr;
    countInfantry = 0;
    countVehicle = 0;
    currSize = 0;
}
// Hàm truy cập sâu vào đơn vị Unit 
 Unit* UnitList::deepCopyUnit(Unit* unit){
    if (!unit) return nullptr;
    int q = unit -> getquantity();
    int w = unit -> getWeight();
    Position newPos = unit ->getCurrentPosition();  // Lấy vị trí pos mới của trận địa 
    Unit *deepUnit =  nullptr;
    if (isVehicleType(unit)){  // Kiểm tra xem unit trên có phải là Vehicle hay ko 
        deepUnit =  new Vehicle (q,w,newPos,(VehicleType)unit -> checkValue());  // Lấy kiểu dữ liệu thích hợp cho deepUnit
    } else {
        deepUnit =  new Infantry (q,w,newPos,(InfantryType)unit -> checkValue());
        // Lấy đơn vị phù hợp cho deepUnit nếu là Infantry 
    }
    deepUnit -> setAttackScore( unit -> getAttackScoreDuringFight());  // Thực hiện lấy chỉ số chiến đấu cho attackScore  trước khi lâm trận 
    return deepUnit;
 }
// Chèn cho Vehicle vào cuối danh sách 
void UnitList::insertAtEnd (Unit * unit){
    Node *newNode = new Node (deepCopyUnit(unit)); // Khởi tạo node mới xử lý trên danh sách Deep Copy
    if (! tail ) {
  // Lấy phần đuôi trỏ đến ngay phần tử mới insert at the end list 
        head = tail= newNode;  
    }
    else {
        tail -> next = newNode;
        tail = newNode;
    }
}
Unit* UnitList:: identifyUnit (Unit * unit){  // Hàm tìm kiêm phương thức UNIT đầu vào
    return isVehicleType(unit) ? identifyUnit((VehicleType)unit-> checkValue()) 
                                        :  identifyUnit((InfantryType)unit-> checkValue());
}
Unit*  UnitList:: identifyUnit (InfantryType type){  // Check có phải là kiểu dữ liệu Infantry
    for (Node * curr = head; curr;curr= curr-> next){
        if (isInfantryType(curr-> unit) && curr -> unit -> checkValue() == type ) return curr -> unit;
    }
    return nullptr;
}
Unit* UnitList:: identifyUnit (VehicleType type){  // Check xem có phải là kiểu dữ liệu Vehicle 
    for (Node * curr = head; curr;curr= curr-> next){
        if (isVehicleType(curr-> unit) && curr -> unit -> checkValue() == type ) return curr -> unit;
    }
    return nullptr;
}
bool UnitList::insert(Unit *unit)
{
    // TODO: Implement
    // Nếu ko còn vị trí thêm vào trong danh sách thì ko thêm 
    // currSize = getcountInfantry() + getcountVehicle();
    if (unit == nullptr|| getcountInfantry()+getcountVehicle() >= capacity) {  //Hai số lượng trưng dụng này ý muốn nói đến currSize hiện tại
        // cout<<"Your list is overloading";
        return false;  // Ko thêm vào danh sách 
    }
    // Nếu là Unit đã có sắn trong danh sách thì chỉ cập nhật lại số lượng quantity 
    if (isContain(unit)){
        Unit *identity = identifyUnit (unit);
        if (identity) {
            updateQuantity(identity,unit);  
        }// Nếu con trỏ identity trả về giá trị thì đúng nếu là nullptr thì kết quả là sai
        return false; // Bởi chỉ return true nếu insert thành công
        // Nếu tồn tại thì ko cần insert
    }
    // Cẩn kiểm tra phân định rõ hai trường hợp 
    // Nếu là vehicle chèn vào cuối list 
    Unit * newUnit = deepCopyUnit(unit);  // Can thiệp sâu vào danh sách bằng newUnit
    Node * newNode = new Node (newUnit);   // Khởi tạo một node mới bằng unit can thiệp mới 
    if (isInfantryType(newUnit)){  // Kiểm tra xem đơn vị unit có đơn vị Infantry hay không
      // Nếu là lực lương bộ binh infantry chèn vào đầu list 
        newNode -> next = head;
        head = newNode;
        if (!tail) tail = newNode;
        countInfantry++; // Cập nhật đếm số lượng Infantry lực lượng bộ binh
    } else {
        // Chèn vào cuối danh sách nếu là Vehicle 
        insertAtEnd (newUnit);
        countVehicle++;
    }
    currSize++;
    return true;
}
// Kiểm tra và tăng quantity nếu Unit đã tồn tại trong danh sách 
void UnitList ::updateQuantity(Unit* unitCurrent, Unit* addUnit){
    if (unitCurrent -> getWeight()< addUnit-> getWeight()) {
        // Cập nhật lại weight và pos
        unitCurrent ->setWeight(addUnit-> getWeight());
        unitCurrent -> setPos(addUnit->getCurrentPosition());
    }
    unitCurrent -> setquantity(unitCurrent -> getquantity()+ addUnit-> getquantity());
    unitCurrent -> setAttackScore(unitCurrent -> getAttackScore());
  }
// Hàm xóa đơn vị unit khỏi liên kết nếu là unit ko hợp lệ
void UnitList::remove(Unit *unit) {  // Xóa đơn vị Unit theo yêu cầu ra khỏi danh sách 
    // TODO: Implement
    if (!unit || ! head) return; // Nếu đơn vị unit và head trong danh sách hiện tại thì thoát ra 
    // Nếu node ban đầu trong danh sách là Node cần xóa 
    if (head-> unit ->str() == unit -> str()){
        Node *tempo =head;
        head = head -> next;
        if (head == nullptr) tail = nullptr;
        delete tempo -> unit;
        delete tempo; 
        return;
    }
    // Cần tìm Node đứng trước Node cần xóa 
    Node * previous = head;
    while (previous -> next && previous-> next-> unit -> str() != unit -> str() ){
        previous = previous -> next;
    }
    // Nếu ko tìm thấy 
    if (! previous -> next) return;
    // Xóa node tìm được 
    Node * erase = previous ->next;
    previous -> next = erase -> next;
    if (erase == tail) tail = previous;
    delete erase -> unit;
    delete erase ;    
}
// Hàm duyệt danh sách xem unit là vehicle đã tồn tại hay chưa 
bool UnitList::isContain(VehicleType vehicleType)
{
    // TODO: Implement
    Node * current = head;
    while (current){
        if (isVehicleType(current -> unit )){
            if (current -> unit -> checkValue() == vehicleType) return true;
        }
        current = current -> next;
    }
    return false;
}
// Kiểm tra xem danh sách đã tồn tại infantry này chưa 
bool UnitList::isContain(InfantryType infantryType)
{
    // TODO: Implement
    Node * current = head;
    while (current){
        if (isInfantryType(current -> unit )){
            if (current -> unit -> checkValue() == infantryType) return true;
        }
        current = current -> next;
    }
    return false;
}
// Hàm duyệt xem unit đã tồn tại trong danh sách Vehicle hoặc Infantry hay không 
bool UnitList::isContain(Unit* unit)
{
     return isVehicleType(unit) ? isContain((VehicleType)unit->checkValue())
                           : isContain((InfantryType)unit->checkValue());
}
string UnitList::str() const
{
    // TODO: Implement
    stringstream ss;
    ss << "UnitList[";
    ss << "count_vehicle=" << countVehicle ;
    ss << ";count_infantry=" << countInfantry;
    // Hàm printLinkedList in các đơn vị linked List 
    if (head){
        ss<<";";
        Node * curr = head;
        while (curr){
            // Unit *unit = curr -> unit ;
            ss<< curr-> unit -> str();
            if (curr -> next) ss<<",";
            curr = curr -> next;
        }
    }
    ss << "]";
    return ss.str();

}
bool  UnitList::isVehicleType(Unit *unit){
// Hàm kiểm  tra xem kiểu giá trị thực sự của Unit là vehicle hay là infantry 
    return dynamic_cast <Vehicle*> (unit) != nullptr;
}
bool  UnitList::isInfantryType(Unit *unit){
// Hàm kiểm tra xem kiểu Unit này có thuộc kiểu đơn vị bộ binh hay ko
  return dynamic_cast <Infantry*> (unit) != nullptr;
}
void UnitList :: reverseList(){
    Node* curr = head;
    Node* prev = nullptr;
    tail = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
 // Khởi tạo cho hàm Constructor Copy tạo bản sao mới từ bản gốc
UnitList::UnitList(const UnitList& other) {
    // clear ();
    // if (!other) return;
    head = tail = nullptr;
    Node* curr = other.getHead();
    // if (!curr) return;
    if (curr) {
        setCapacity(other.getCapacity());
        setcountInfantry(other.countInfantry);
        setcountVehicle(other.countVehicle);
        setCurrSize(getcountInfantry() + getcountVehicle());
    }
    else {
        setCapacity(0);
        setcountInfantry(0);
        setcountVehicle(0);
        setCurrSize(0);
    }
    while (curr) {
        insertAtEnd(curr->unit);
        curr = curr->next;
    }
    
}
// Tạo toán tử operator =
UnitList& UnitList::operator = (const UnitList& others){     // Tạo operator toán tử = gán cho 2 unit list bằng nhau 
    if (this == &others) return *this;

    // this->~UnitList();    
    // Có thể nguy hiểm khi truy xuất trực tiếp 
    clear();
    head = tail = nullptr;
    Node * currence = others.getHead();
    if (currence){
        setcountInfantry(0);
        setCapacity(0);
        setCurrSize(0);
        setcountVehicle(0);
    } else {
        setCapacity(others.getCapacity());
        setcountInfantry(others.countInfantry);
        setcountVehicle(others.countVehicle);
        setCurrSize(getcountInfantry()+ getcountVehicle());
    }

    while (currence){
        insertAtEnd(deepCopyUnit(currence->unit));
        currence = currence -> next;
    }
    return *this;
}
