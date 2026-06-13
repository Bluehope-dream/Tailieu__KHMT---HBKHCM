#include "hcmcampaign.h"
//////////////////////////////////////////////////////////////////////////////////////
////                CLASS POSITION 
////
////////////////////////////////////////////////////////////////////////////////////////
Position::Position(int r, int c) : r(r), c(c)
{
    // TODO: implement

}

Position::Position(const string &str_pos)  // định dạng đọc thông tin  có dạng chuẩn là pos(r,c)
{
    // TODO: implement
    istringstream iss(str_pos);
    char ch;
    int row, col;
    iss>>ch>>row>>ch>>col>>ch;
    r = row;
    c= col;
}

int Position::getRow() const { return r; }

int Position::getCol() const { return c; }

void Position::setRow(int r)
{ // TODO: implement
    this ->r =r;
}

void Position::setCol(int c)
{
    // TODO: implement
    this -> c =c;
}

string Position::str() const
{
    // TODO: implement
    return "("+ to_string(r)+","+to_string(c)+")";
}
/////////////////////////////////////////////////////////////
//             CLASS UNIT         
//
////////////////////////////////////////////////////////////
Unit::Unit(int quantity, int weight, Position pos)
{
    // TODO: implement
    this -> quantity =quantity;
    this -> weight =weight ;
    this ->pos =pos;
    if (this->quantity < 1) this->quantity = 1;
    if (this->weight < 1) this->weight = 1;
}

Unit::~Unit()
{
    // TODO: implement
    // Hàm này yêu cầu cho lớp dẫn xuất phải đc thực hiện hàm hủy nếu có 
}

Position Unit::getCurrentPosition() const  // Hàm này tương đương với hàm 
{
    return pos;
}
void Unit::setquantity(int num){
    quantity = num;
}
int Unit::getquantity(){ return quantity;   }  // Vơi mục đích thiết lập lại quantity cho đôi tượng 
int Unit::getWeight(){ return weight;}
void Unit::setWeight(int weight){this->weight =weight;}
void  Unit::setPos(Position pos){ this-> pos =pos;   }
////////////////////////////////////////////////////////////////////////////////
////                    CLASS VEHICLE 
////
////////////////////////////////////////////////////////////////////////////////
Vehicle::Vehicle (int quantity, int weight, const Position pos,VehicleType
    vehicleType):
        Unit(quantity, weight,pos),
        vehicleType (vehicleType){}

int Vehicle :: getAttackScore () {
    // Nếu mà 2 chỉ số quantity và weight ko hợp lệ thì 
    if (this -> quantity < 1) this -> quantity = 1;
    if (this -> weight < 1 ) this -> weight =1;
    double result = (vehicleType * 304 + quantity * weight)/30.0;  // đảm bảo tính an toàn là một số nguyên khi thực hiện phép toán 
    int res = round (result);
    if (abs(res - result ) <1e-7) return res;
    return static_cast <int> (ceil(result));  // Ep kiểu c++ type sẽ an toàn hơn rất nhiều 
}
// Ánh xạ các phương tiện trong danh sách enum 
string Vehicle::vehicleReflexion(const VehicleType &vehicleName){
    switch (vehicleName){
       case TRUCK : return "TRUCK";
      
       case MORTAR: return "MORTAR";
  
       case ANTIAIRCRAFT: return "ANTIAIRCRAFT";
    
       case ARMOREDCAR: return "ARMOREDCAR";
     
       case APC: return "APC";
    
       case ARTILLERY: return "ARTILLERY";
     
       case  TANK: return "TANK";
    
       default: return"";
    }
}
string Vehicle:: str() const {
     stringstream ss;
     // Viết dòng lệnh in ra màn hình theo cú pháp model cho sẵn 
     ss<<"Vehicle["
        <<"vehicleType="<<vehicleReflexion(this->vehicleType)<<',';
     ss<<"quantity="<<this->quantity<<','
        <<"weight="<<this->weight<<','
        <<"position="<<this->pos.str()<<']';
     return ss.str();
} 
int Vehicle::checkValue() {
    return this -> vehicleType;  // Truy xuất vehicleType để kiểm tra dữ liệu có phải là Vehicle hay không?
}
////////////////////////////////////////////////////////////////////////////////////////////////
////                            INFANTRY CLASS 
///
////////////////////////////////////////////////////////////////////////////////////////////////
int Infantry::safeCeil(double val) {
    double rounded = round(val);
    if (abs(val - rounded) <= 1e-7)
        return static_cast<int>(rounded);
    return static_cast<int>(ceil(val));  
}
bool Infantry::isPerfect(int val){
    if (val<0) return false;
    int root =(int) sqrt(val);
    return root*root == val;
 }
Infantry::Infantry(int quantity, int weight, const Position pos, InfantryType infantryType): Unit(quantity,weight,pos),infantryType(infantryType) {}
int Infantry::getAttackScore() {
    int typeValue = static_cast<int>(infantryType);
    int base = typeValue * 56 + quantity * weight;
    bool isCommando = checkCommando(infantryType, weight);
    if (isCommando) {
        base += 75;
    }
    
    int personal = getPersonalIndex(base);
    if (personal > 7) {
        double res = quantity * 1.2; 
        setquantity(static_cast<int>(std::ceil(res)));
        if (quantity < 1) quantity = 1;
    } else if (personal < 3) {
        double res = quantity * 0.9; 
        setquantity(static_cast<int>(std::ceil(res)));
        if (quantity < 1) quantity = 1;
    }
    
    base = typeValue * 56 + quantity * weight;
    return base;
}
string Infantry::str() const {  // Hàm này có tính chất của một phương thức const nên chỉ có thể gọi bởi phương phương thức const 
    stringstream  ss;
    ss<<"Infantry["<<"infantryType="<<InfantryName(infantryType)<<',';
    ss<<"quantity="<<quantity<<',';
    ss<<"weight="<<weight<<',';
    ss<<"position="<<pos.str()<<']';
    return ss.str();
}
bool Infantry::checkCommando (InfantryType &value, int &weight){
    if (value != SPECIALFORCES) return false;
    if (isPerfect(weight)) return true;
    return false;
}
int Infantry::getPersonalIndex(int &score){
    // Hàm tính tổng các chữ số của một năm 
    int sum=0, year=1975;  // Trong bài toán này chỉ xét 
    while (year>0){
        sum += year %10;
        year /=10;
    }
    int tempo = score;
    while (tempo>0){
        sum+= tempo % 10;
        tempo/=10;
    }
    //ham rut gon cac chu so 2 chu so ve con 1 chu so
    while (sum >= 10) {
        tempo = sum;
        sum = 0;
        while (tempo > 0) {
            sum += tempo % 10;
            tempo /= 10;
        }
    }
    return sum;
}
// Hàm ánh xạ infantryType
string Infantry::InfantryName(const InfantryType &value) const {
    switch (value){
          case SNIPER: return "SNIPER";
          case ANTIAIRCRAFTSQUAD: return "ANTIAIRCRAFTSQUAD";
          case MORTARSQUAD: return "MORTARSQUAD";
          case ENGINEER: return "ENGINEER";
          case SPECIALFORCES: return "SPECIALFORCES";
          case REGULARINFANTRY: return "REGULARINFANTRY";
          default : return "";
    }
}
// Câu lệnh đè kiểm tra kiểu dữ liệu cho bộ binh 
 int Infantry:: checkValue() {
    return  infantryType;
 }

//////////////////////////////////////////////////////////////////////////////////////////
////            ARMY CLASS
////
//////////////////////////////////////////////////////////////////////////////////////////
bool Army::checkSpecialNumber(int val){  // Có thể Sử dụng thuật toán vét cạn backTracking để tính toán 
    if (val<=0) return false;
    const int base [] = {3,5,7};  // Xác định cơ số nó là một số nguyên tố lẻ nhỏ hơn 10
    for (int i: base){
        if (isSpecialNum(val,i)) return true;
    }
    return false;
}
bool Army:: isSpecialNum(int val, int n){
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
Army::Army(Unit** unitArray, int size, string name,BattleField* battleField) : name(name),battleField(battleField)
{
    // TODO: Implement
    if (size == 0) {
        LF = 0;
        EXP = 0;
        unitList = new UnitList(0);  // Không có sức chứa cho đơn vị quân sự
    }
    else {
        LF = 0;
        EXP = 0;
        for (int i = 0; i < size; ++i) {
            // cout<<"LF "<<getLF()<<"EXP "<< getEXP()<<" ";
            unitArray[i]->setAttackScore(unitArray[i]->getAttackScore());
            if (dynamic_cast<Vehicle*>(unitArray[i]) != nullptr) LF += unitArray[i]->getAttackScoreDuringFight();
            else EXP += unitArray[i]->getAttackScoreDuringFight();
        }

        checkLFrange(LF);
        checkEXPrange(EXP);
        int sum = EXP + LF;
        if (checkSpecialNumber(sum)){
            unitList = new UnitList(12);
        } else {
            unitList = new UnitList(8);
        }
        for (int i = 0; i < size; i++) {
            unitList->insert(unitArray[i]);
        }
       
    }     
}

Army::~Army() {
    // TODO: Implement

    // Xóa danh sách UnitList khi báo cho Linked List 
    delete unitList;
}
void Army::findMinestGreaterLiberArmy(vector<Unit*>& setOfInfantry, vector<Unit*>&setOfVehicle,vector<Unit*>&A,vector<Unit*>&B,UnitList* unitList,int minLF , int minEXP){
    for (UnitList:: Node* current = unitList -> getHead(); current;current = current-> next)
    if(unitList -> isVehicleType(current -> unit)) {
        setOfVehicle.emplace_back(deepCopyUnit(current-> unit));
    } else {
        setOfInfantry.emplace_back(deepCopyUnit(current -> unit));
    }
    A = SubMinScore(setOfVehicle,minLF);
    B = SubMinScore(setOfInfantry,minEXP);
}
vector<Unit*> Army::SubMinScore(vector<Unit*> units, int minTotal) {
    int n = units.size();
    vector<Unit*> bestSubset;
    int bestScore = INT_MAX;

    for (int mask = 1; mask < (1 << n); ++mask) {
        int sum = 0;
        vector<Unit*> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += units[i]->getAttackScoreDuringFight();
                subset.push_back(units[i]);
            }
        }
        if (sum >= minTotal && sum < bestScore) {
            bestScore = sum;
            bestSubset = subset;
        }
    }

    return bestSubset;
}
void Army::fight(Army* enemy, bool defense) {
    // TODO: Implement
}

string Army::str() const {

    return""; // Không trả về hàm gì cả bản chất cúa hàm này chỉ là hàm ghi đè 
}

int Army::safeCeil(double val) {
    int  rounded = round(val);
    if (abs(val - rounded) < 1e-7)
        return (int)val;
    return static_cast<int>(ceil(val));  
}

void Army::checkLFrange(int &val){
    if (val<0) val = 0;
    else if (val > 1000) val = 1000;

}
void Army::checkEXPrange(int &val){
    if (val <0) val =0;
    else if (val>500) val =500;

}
Unit* Army::deepCopyUnit(Unit* unit){      // Tạo bản sao truy cập sâu vào hàm Unit
    if (!unit) return nullptr;
    int q = unit -> getquantity();
    int w = unit -> getWeight();
    Position newPos = unit -> getCurrentPosition();  // Lấy vị trí pos mới của trận địa 
    Unit *deepUnit;

    // Đặc tả danh sách cập nhật cho các đơn vị
    if (unitList -> isVehicleType(unit)){  // Kiểm tra xem unit trên có phải là Vehicle hay ko 
        deepUnit =  new Vehicle (q,w,newPos,(VehicleType)unit -> checkValue());  // Lấy kiểu dữ liệu thích hợp cho deepUnit
    } else {
        deepUnit =  new Infantry (q,w,newPos,(InfantryType)unit -> checkValue());
        // Lấy đơn vị phù hợp cho deepUnit nếu là Infantry 
    }
    deepUnit -> setAttackScore( unit -> getAttackScoreDuringFight()) ; // Thực hiện lấy chỉ số chiến đấu cho attackScore  trước khi lâm trận 
    return deepUnit;
}
UnitList* Army :: deepCopyUnitList(UnitList * tempo) {
    if (!tempo -> getHead()) return nullptr;
    UnitList * deep = new UnitList(1);
    deep -> setCapacity(tempo -> getCapacity());
    for (UnitList:: Node *node = tempo -> getHead() ; node ; node = node -> next){
        deep -> insertAtEnd(node-> unit);
        if (deep -> isVehicleType(node -> unit) ) deep -> setcountVehicle(deep-> getcountVehicle()+1);
        else deep -> setcountInfantry(deep -> getcountInfantry() + 1);
        deep -> setCurrSize(deep ->getcountInfantry() + deep -> getcountVehicle());
    }
    return deep;
 }   

 // Thiết lập thông số danh sách khi loại unit ra khỏi linked List
 void Army:: eliminateUnit(UnitList* list, Unit * unit ){
    if (list->isVehicleType(unit)) {
        list->setcountVehicle(list->getcountVehicle() - 1);
    }
    else {
        list->setcountInfantry(list->getcountInfantry() - 1);
    }
 }
void Army:: setAttackScore (){  // Thiết lập các chỉ số Score cho toàn bộ Unit
    UnitList:: Node *edge = unitList -> getHead();
    while (edge){
        edge -> unit -> setAttackScore( edge -> unit -> getAttackScore ());  // Lấy các chỉ số giao tranh từ các attackScore tương ứng 
        edge = edge -> next;
    }
}
void Army::findLFEXP(){
    // Hàm cập nhật các chỉ số quân sự LF và EXP 
    LF = EXP =0;
    UnitList:: Node* at = unitList->getHead();
    while (at){
        if (unitList -> isInfantryType(at -> unit)){
            EXP += at -> unit -> getAttackScoreDuringFight();
        }
        else {
            LF += at -> unit -> getAttackScoreDuringFight();
        }
        at = at -> next;
    }
    checkLFrange (LF);
    checkEXPrange(EXP);
}
void Army::printAfterWar (){
    if (this->unitList->getHead() == nullptr) return;
    UnitList* cloned = deepCopyUnitList(this->unitList);
    UnitList::Node* curr = cloned->getHead();
    bool isChange = false;
    while (curr) {
        if (curr->unit->getAttackScoreDuringFight() <= 5) {
            isChange = true;
            this->unitList->remove(curr->unit);
        }

        curr = curr->next;
    }

    curr = cloned->getHead();
    while (curr) {
        delete curr->unit;
        curr = curr->next;
    }
    delete cloned;

    bool check = (isChange || !this -> fighting);
    if (check) {
        setAttackScore();
        findLFEXP();
    }

  }
////////////////////////////////////////////////////////////////////////////////////////////////
////
////                        LIBERATION ARMY CLASS 
////
/////////////////////////////////////////////////////////////////////////////////////////////////
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name,BattleField* battleField)
                                                : Army(unitArray,size,name,battleField) {                                                       
    // TODO: Implement
}

void LiberationArmy::fight(Army *enemy, bool defense){
    // TODO: Implement
// Xét hàm defense là true (cho tấn công )
if (!defense ){  // Trường hợp xét hàm defense là false (đang ở thế tấn công )
    bool skipBattle = false;
    bool champion = false;
    // Tìm tổ hợp phù hợp cho sức mạnh quân đội
    findMinestGreaterLiberArmy(setOfVehicle,setOfInfantry,A,B,unitList,enemy -> getLF() ,enemy -> getEXP());
    if (!A.empty() && !B.empty()){
         setFighting();
        int numA = unitList-> getcountVehicle()-A.size();
        int numB = unitList->getcountInfantry() - B.size();

        eraseInvalidCombo(A);
        eraseInvalidCombo(B);
        unitList -> setcountVehicle(numA);
        unitList -> setcountInfantry(numB);
        champion = true;
            liberChampion = true;
        // Cập nhật phương thức truy cập kịp thời cho các thông tin về chỉ số 
        upload(enemy -> unitList);
        enemy -> setAttackScore(); // Cập nhật lại chỉ số chiến đấu AttackScore cho kẻ thù 
        enemy -> findLFEXP(); // Cập nhật lại chỉ số cho LF và EXP cho kẻ thù enemy 
                        
    } else if (! A.empty()&& B.empty() ){
        // xÉT CÁC CHỈ SỐ CỦA ĐỐI PHƯƠNG CHIẾN ĐẤU
        int tempo = safeCeil(1.5*EXP);
        checkEXPrange(tempo);     // Dặt điều kiện so sánh nếu nó vượt quá tầm kiểm soát 
        if (tempo > enemy -> getEXP()){
        setFighting();
        eraseInvalidCombo(A);
        eraseInvalidCombo(setOfInfantry);
        unitList -> setcountVehicle(unitList -> getcountVehicle()-A.size());
        unitList -> setcountInfantry(0);
        champion = liberChampion = true; // Quân đội ra sức chiến thắng     // Chiến thắng thuộc về Quân Giai Phóng 
        // Cập nhật lại kịp thời các thông số sau khi giao tranh xảy ra 
        upload(enemy -> unitList);
        enemy -> setAttackScore();
        enemy -> findLFEXP();
        } else if (tempo <= enemy -> getEXP()){
            skipBattle = true;  // Tránh đc tác động tham chiến 
        }
        // cout<<"Hello "<< getEXP();
    }
    else if  (! B.empty()&& A.empty() ){
    // xÉT CHỈ SỐ CHIẾN ĐẤU LF của đối phương 
        int key = safeCeil (1.5*LF) ;
        checkLFrange(key);
        if (key > enemy -> getLF()){
             setFighting();
            eraseInvalidCombo(setOfVehicle);
            eraseInvalidCombo(B);
            unitList -> setcountVehicle(0);
            unitList -> setcountInfantry(unitList -> getcountInfantry() - B.size());
            champion = true; // Quân đội ra sức chiến thắng 
        // Cập nhật lại kịp thời các thông số sau khi giao tranh xảy ra 
            upload(enemy -> unitList);
            enemy -> setAttackScore();
            enemy -> findLFEXP();
        // cout<<"Bye "<< getEXP();
        } else if (key <= enemy -> getLF()){
            skipBattle = true;     // Tránh tác đông của cuộc chiến 
        }
    }
    else if (A.empty()&& B.empty()){
        // Xảy ra phương thức hòa hoãn 
        skipBattle = true; // Thể hiện  trạng thái ko giao tranh 
    }
    if (champion){
        // Nếu chiến thắng 
        // Cập nhật lại các chỉ số chiến tranh AttackScore , và LF, EXP
        // Tạo 1 hàm filp war là gì  DÊN TASK 4 CẬP NHẬT LẠI
         setFighting();
        setAttackScore();
        findLFEXP();
    }
    if (skipBattle){  // Nếu ko xảy ra giao tranh 
        
        for (UnitList:: Node* p = unitList -> getHead();p != nullptr; p=p-> next){
            Unit * u = p-> unit;
            const double res = (double) u->getWeight() * 9.0/10.0;
            u-> setWeight(safeCeil(res));
            u-> setAttackScore( u-> getAttackScore());
        }
        liberChampion= false;
        findLFEXP();
    }
} else {   
// Xét hàm defense là true  (cho phòng thủ của quân giải phóng  )
    LF = safeCeil (1.3 * static_cast<double>(LF));
    checkLFrange(LF);
    EXP = safeCeil (1.3 * static_cast<double> (EXP));
    checkEXPrange (EXP);
    if ( LF >= enemy -> getLF() && EXP >= enemy -> getEXP())  return;
    if (LF < enemy -> getLF () && EXP < enemy -> getEXP()){
        bool check = (LF >= enemy->getLF() && EXP >= enemy->getEXP() )|| (LF >= enemy->getLF() && EXP < enemy->getEXP())
                        || (LF < enemy->getLF() && EXP >= enemy->getEXP());
        while (!(check)){  // Nếu cả 2 chỉ số đều nhỏ hơn cần chi viện
            for (UnitList:: Node* p = unitList -> getHead(); p!= nullptr;p = p-> next){
                Unit * u = p-> unit;
                u-> setquantity(findNearestFibonacci(u-> getquantity()));  // Cập nhật lại số đơn vị quân sự quantity với giá trị gần Fibonarci nhất 
                u-> setAttackScore (u -> getAttackScore());   // Cập nhật lại chỉ số chiến đấu 
            }
            findLFEXP();
            LF = safeCeil(1.3*(double)LF);
            EXP = safeCeil (1.3*(double)EXP);
            checkEXPrange(EXP);
            checkLFrange(LF);
        }
        if ( LF >= enemy -> getLF() && EXP >= enemy -> getEXP())  return;
    }
        for (UnitList :: Node *p = unitList -> getHead();p; p=p-> next){
            Unit*u = p-> unit;
            u-> setquantity(safeCeil((double)u-> getquantity()*0.9));
            u-> setAttackScore (u -> getAttackScore());
        }
        findLFEXP();
        checkLFrange(LF);
        checkEXPrange(EXP);
        // cout<<"Liberty --LF "<<getLF()<<"EXP "<<getEXP()<<endl;
        // cout<<"Enemy --LF "<<enemy->getLF()<<"EXP "<< enemy->getEXP()<<endl;
   }
}
string LiberationArmy::str() const {
    // TODO: Implement
    stringstream ss;
    ss<<"LiberationArmy[LF="<<LF;
    ss<<",EXP="<<EXP;
    ss<<",unitList="<<unitList-> str();
    ss<<",battleField=";
    if (battleField) ss<< battleField -> str();
    ss<<"]";
    return ss.str(); // Hàm trả về chuỗi thông tin này bằng 
}


// Support  function: Tìm số fibornanci gần nhất 
int LiberationArmy::findNearestFibonacci(int value) {
    // TODO: Implement
    if (value <= 0 ) return 1;
    int F0 =1, F1 =1;
    int Fibo = F0 + F1;
    while (Fibo <= value){
        F0=F1;
        F1 = Fibo;
        Fibo = F0 + F1;
    }
    return Fibo;
}

void LiberationArmy::upload (UnitList* enemyList ) {  // Chỉ số đơn vị của kẻ thù cần đc cập nhật 
// Phương thức kịp thòi cập nhật lại các chỉ số giao tranh
    UnitList * clone = deepCopyUnitList(enemyList);
    clone -> reverseList();
    for (UnitList::Node*p =clone-> getHead();p!=nullptr; p= p-> next){
    
        if (this -> unitList -> insert (p-> unit)){
            eliminateUnit(enemyList,p-> unit);
            enemyList -> remove(p-> unit);
        } else if (this ->unitList -> isContain(p-> unit)){
            Unit* exist = this -> unitList -> identifyUnit(p-> unit);
            if (exist -> getWeight() < p-> unit -> getWeight()){
                exist -> setWeight(p-> unit-> getWeight());
            }
            exist -> setAttackScore (exist -> getAttackScore());
            eliminateUnit(enemyList,p->unit);
            enemyList -> remove(p-> unit);
        }
    }
    delete clone;  // Giải phóng vùng nhớ khi cấp nhát deepCopy cho unitList
}
 void LiberationArmy::eraseInvalidCombo(vector<Unit*>& combo ){
// Xóa các tổ hợp ko phù hợp và các  đơn vị tương ứng 
   for (Unit * u : combo){
        unitList -> remove(u);
   }
 }
void LiberationArmy::clearVector(vector<Unit*> &vector ){
     while (!vector.empty()){
        vector.pop_back();
    }
 }
 LiberationArmy::~LiberationArmy(){                                                       
    // TODO: Implement
    if (! setOfInfantry.empty()) clearVector(setOfInfantry);
    if (! setOfVehicle.empty()) clearVector(setOfVehicle);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
////                ARVN ARMY CLASS 
////
///////////////////////////////////////////////////////////////////////////////////////////////////////
ARVN::ARVN(Unit** unitArray, int size, string name,BattleField* battleField)
    : Army(unitArray, size, name,battleField) {
        // TODO: Implement
}
void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
    bool attackWar =false;       // Mặc định trận chiến chưa xảy ra
    if (defense == false ){
        // Thể hiện sự tấn công của quân đội cộng hòa
        attackWar = true;
        for (UnitList :: Node * tempo = unitList -> getHead(); tempo != nullptr; tempo =tempo -> next){
            Unit* u = tempo -> unit;
            u-> setquantity(safeCeil(0.8 * (double) u-> getquantity()));
            if (u -> getquantity() >1){  // Xét quantity >1
                tempo = tempo-> next;
            } 
            else {  // Xét quantity <=1
                if (unitList -> isInfantryType(u)){  // Nếu kiểu dữ liệu là Infantry type 
                    unitList -> setcountInfantry(unitList -> getcountInfantry()-1);
                } else if (unitList -> isVehicleType(u)){  // Nếu kiểu dữ liệu là Vehicle Type
                    unitList -> setcountVehicle(unitList -> getcountVehicle() -1);
                }
            UnitList :: Node *nextNode = tempo -> next;
            unitList -> setCurrSize(unitList -> getcountInfantry()+ unitList ->getcountVehicle());
            unitList -> remove (u);   // Xóa phần tử unit ra khỏi danh sách 
            tempo = nextNode;
        } 
    }
    }
    else {  // defense = true
        // Thể hiện trạng thái phòng thủ của quân đội cộng hòa 
    // Khi xảy ra giao tranh quân đội Sài Gòn thất bại trọng số weight của đơn vị mất đi 20% tức là còn lại 80% sức mạnh 
    // Do đó cần khai báo thông tin cho
        vector<Unit*> setOfVehicle,setOfInfantry, A,B;
            // Đại diện A ý muốn lấy tổ hợp thỏa cho vehicle chỉ số LF
            // Đại diện B ý muốn lấy tổ hợp thỏa cho Infantry (lực lượng bộ binh) chỉ số EXP
            // Chọn tổ hợp phù hợp cho kẻ thù 
        enemy->findMinestGreaterLiberArmy(setOfVehicle,setOfInfantry, A,B,enemy-> getUnitList(),getLF(),getEXP());
            // Sự khó khăn và nhọc nhằn ở bài tập này là cần cập nhật cả về chỉ số sức mạnh và năng lực hiện tại của 
            // ta và kẻ thù 
        bool check =(((!A.empty() && !B.empty() )|| (!A.empty() && safeCeil(1.5*enemy->getEXP())> EXP ) ||
                            (!B.empty() && safeCeil(1.5*enemy-> getLF()) > LF )) && enemy -> liberChampion);
        if (check) {
            upload(enemy -> getUnitList()); // Cập nhật lại chỉ số thông tin unitList
            attackWar =true;
        } else { attackWar = false;                         // Tham chiến ko xảy ra 
        }
                // Khi skipBattle = false (ko giao tranh) đơn vị đc bảo toàn 
        // Giai phóng vùng nhớ thủ công cho các đơn vị Unit
        for (Unit* u: setOfVehicle){
            delete u; // Xóa từng đối tượng trên vùng nhớ 
        }
        setOfVehicle.clear();  // Giai phóng vùng nhớ danh sách 
        for (Unit* u: setOfInfantry){
            delete u;
        }
        setOfInfantry.clear();
    }
    if (attackWar){
        setFighting();
        findLFEXP();
        setAttackScore();
    }
    checkEXPrange(EXP);
    checkLFrange(LF);
}


string ARVN::str() const {
    // TODO: Implement
    stringstream ss;
    ss<<"ARVN[LF="<<LF;
    ss<<",EXP="<<EXP;
    ss<<",unitList="<<unitList-> str();
    ss<<",battleField=";
    if (battleField) ss<<battleField-> str();
    ss<<"]";
    return ss.str();
}
ARVN :: ~ARVN(){}  // Tạo destructor rỗng cho phần khởi tạo
// Viết hàm cập nhật cho  vấn đề upload các chỉ số của đội quân chiến tranh cho quân đội cộng hòa 
void ARVN:: upload(UnitList* List){
    // UnitList* LiberList = deepCopyUnitList(List); //Tạo hàm truy cập sâu vào đối tượng list trên 
                                     UnitList* LiberList = List;
    unitList -> reverseList();  // Đảo danh sách đơn vị
    UnitList::Node* tempo = unitList -> getHead();
    int validCount =0;
    while (tempo){
        if (LiberList -> insert (tempo-> unit) || LiberList -> isContain(tempo-> unit)){
            validCount++;
        }
        tempo= tempo -> next;
    }
    tempo = unitList -> getHead();
    while (tempo != nullptr && validCount >0){
            Unit* u = tempo -> unit;
            u-> setWeight(safeCeil(0.8*(double) u -> getWeight()));
        validCount--;
        tempo = tempo -> next;
    }
    unitList -> reverseList();
    delete LiberList;  // từ từ khi tổng hợp code rồi mói để tạo ra 
    // Giải phóng vùng nhớ HEAP đang đc cấp phát 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
////
////                    CLASS UNITLIST 
////
//////////////////////////////////////////////////////////////////////////////////////////////////////
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

UnitList::UnitList(int capa) : head(nullptr),tail(nullptr),countInfantry(0), countVehicle(0), currSize (0)
{
    // TODO: Implement
    // Xét S để dưa ra chỉ số nếu S là special Num thì capacity = 12, còn ko nó chính là 8 
   capacity = capa;
   if (capa < 0) capacity =0;
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
    
    if (unit == nullptr|| getcountInfantry()+getcountVehicle() >= capacity) {  //Hai số lượng trưng dụng này ý muốn nói đến currSize hiện tại
        
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
//-----------------------------------------------------
// CLASS TerrainElement và các lớp dẫn xuất
//-----------------------------------------------------
TerrainElement::TerrainElement(Position pos) : pos(pos)
{}

TerrainElement::~TerrainElement() {}
    // Giải phóng tài nguyên nếu có
// Road: không có hiệu ứng
void Road::getEffect(Army *army) {
    // Không gây ảnh hưởng cho quân đội.(kể cả phe tấn công và phòng thủ )
    return;
}
Road::~Road(){}
// Mountain: stub – áp dụng hiệu ứng cho các đơn vị trong bán kính ảnh hưởng (theo đề bài, hiệu ứng có thể là:
// tăng EXP của bộ binh và giảm LF của phương tiện, tùy thuộc vào khoảng cách)
void Mountain::MountainEffect(double &addSum, double &minusSum,double &addIndex, double &minusIndex,UnitList *list,double &r){
    if (!list) return;
    for (UnitList::Node* tempo = list->  getHead();tempo != nullptr;tempo = tempo-> next){
        Unit* u = tempo -> unit;
        double D =static_cast<double> (calDistance(this-> pos,u-> getCurrentPosition()));
        if (D > r) continue; // Không có bất kỳ sự cập nhật nào với  
        // Sử dụng dynamic_cast(<>) // để tiếp kiểu dữ liệu của lớp đó 
        if (dynamic_cast<Vehicle*>(u)) {
            minusSum -= minusIndex *static_cast<double>(u -> getAttackScoreDuringFight());
        } else {  // cập nhật lấy attackScore của 
            addSum += addIndex* static_cast<double> (u -> getAttackScoreDuringFight());
        }
        minusSum = safeCeil(minusSum);
        addSum = safeCeil(addSum);
    }
}
void Mountain::getEffect(Army *army) {
    if(army == nullptr || ! army -> getUnitList()) return;
    double LF = army -> getLF();
    double EXP = army -> getEXP();
    // Kiểm tra đầu vào là quân đội cộng hòa hay là quân giải phóng 
    double a,b,base;
    if (dynamic_cast<LiberationArmy*>(army)){
        a=0.3;
        b=0.1;
        base = 2.0;
        MountainEffect(EXP,LF,a,b,army -> getUnitList(),base);
    } else {
        a=2;
        b=0.05;
        base =4.0;
        MountainEffect(EXP,LF,a,b,army -> getUnitList(),base);
    }
    army -> setEXP(safeCeil(EXP));
    if (army -> getEXP() <0 ) army -> setEXP(0);
    else if(army -> getEXP() >500) army -> setEXP(500); // Cần cập nhật lại giá trị EXP nằm [0,500]
    army -> setLF(safeCeil(LF));
    if (army -> getLF() <0 ) army -> setLF(0);
    else if(army -> getLF()  > 1000) army -> setLF(1000);
    return;
}
Mountain::~Mountain(){}  // Giải phóng  tài nguyên nếu cần thiết 
// River: stub – giảm EXP của lực lượng bộ binh 10% nếu nằm trong bán kính 2 đơn vị
void River::getEffect(Army *army) {
  if (army == nullptr) return;
  UnitList * list = army -> getUnitList(); // lấy danh sách cho đơn vị UnitList 
//   if (!list) return;
  for (UnitList :: Node* p =army -> getUnitList()-> getHead();p;p=p-> next){
      if(Infantry* force = dynamic_cast<Infantry*>(p-> unit)){
        double distance = calDistance(pos, p-> unit -> getCurrentPosition());
        if (distance <= 2.0){
            double fixedScore =  (double) (p-> unit -> getAttackScoreDuringFight())*0.9;
            p-> unit -> setAttackScore(safeCeil (fixedScore));
        }
      }
  }
}
River::~River(){}
// Urban: stub – hiệu ứng khu dân cư có thể thay đổi attackScore của bộ binh hoặc phương tiện tùy vào loại
void Urban::getEffect(Army *army) {
// Bài toán  xác định khu dân xư cho lớp này 
    if (!army || ! army -> getUnitList()) return; // Nếu ko có quân đội tham chiến trên địa hình thì vượt qua 
    LiberationArmy* LiberationArmyCheck = dynamic_cast<LiberationArmy*>(army);
    if (LiberationArmyCheck){      // Chiến thần 1 Quân giải phóng
        for (UnitList::Node* p = army -> getUnitList() -> getHead(); p; p=p-> next){
        // Kiểm tra đưa đầu vào xem là lực lượng bộ binh hay là phương tiện vehicle
        // Để xét đến attackScore của mỗi phương tiện chiến đấu 
            Unit * u = p-> unit;
     
      // Đọc kiểu trả về của quân đội 
            if(dynamic_cast<Infantry*> (u) != nullptr){
                if (u->checkValue() == InfantryType::SPECIALFORCES  || u -> checkValue() == InfantryType:: REGULARINFANTRY){
                    // Tính khoảng cách Euler của các đơn vị bộ binh 
                    double D = calDistance(pos,u-> getCurrentPosition());
                    // NẾU là lực lượng đặc biệt SPECIALFORCES hoặc lựu lượng thường trực REGULARINFANTRY
                    if (D !=0 && D<=5){
                 // Nếu INFANTRY là SPECIALFORCES hoặc REGULARINFANTRY trong bán kính 5 đơn vị tăng 
                        double base = static_cast<double>  (u -> getAttackScoreDuringFight() + 2.0 * (u -> getAttackScore())/D);
                        u -> setAttackScore(safeCeil(base));
                    }
                }
            }
                else {// Nếu là ARTILLERY lực lượng pháo binh sẽ bị giảm 50% attackScore nếu nằm trong bán kính 2 đơn vị(Nằm trong class Vehicle )
                    if (u-> checkValue() == VehicleType::ARTILLERY){  // Nếu là lực lượng pháo binh 
                        // Tính khoảng cách Euler của các đơn vị bộ binh 
                        double D = calDistance(pos,u-> getCurrentPosition());
                        if ( D <= 2) {
                            double base = static_cast<double>( (u-> getAttackScoreDuringFight())*  0.5);
                            u -> setAttackScore(safeCeil(base));
                        }   
                    }   
                }   
            }        
    }
        else {
            // chiến thần 2 ARVN (Quân đội cộng hòa )
            // Có thể bỏ qua phương thức đối chiệu cho hàm ARVN (do tính 2 là tính duy nhất có thể được xác định)
            UnitList::Node * tempo = army -> getUnitList()-> getHead();
            while ( tempo != nullptr){
        // Nếu INFANTRY là REGULARINFANTRY (QUÂN ĐỘI CHỦ LỰC ) nằm trong bán kính 3 đơn vị khoảng cách 
                Unit *u = tempo -> unit;
                if(dynamic_cast<Infantry*>(u) != nullptr && u -> checkValue() == InfantryType::REGULARINFANTRY){
                    double D = calDistance(pos,u-> getCurrentPosition());
                    if ( D != 0 && D <= 3) {  // tạo điều kiện cho phép chia có nghĩa
                        double res = static_cast<double> (u-> getAttackScoreDuringFight() + 3.0* (u-> getAttackScoreDuringFight()) / (2.0*D));
                        u-> setAttackScore(safeCeil(res));
                    }
                    // Các phương tiện khác của quân đôi cộng hóa ko bị ảnh hưởng 
                }
                tempo = tempo -> next;        
            }
        }
        return;  // Thoát khỏi fucntion
}
Urban::~Urban(){}
// Fortification: stub – hiệu ứng chiến hào, áp dụng cho cả hai quân đội với các thay đổi nhất định
void Fortification::getEffect(Army *army) {  // Phương thức chiến hào 
    if (!army || ! army -> getUnitList()) return; // Nếu ko có quân đội tham chiến trên địa hình thì vượt qua     
    UnitList::Node* p = army -> getUnitList() -> getHead();
    bool isLiberation = dynamic_cast<LiberationArmy*>(army) != nullptr ;
        // Tạo thế chủ động cho quân giải phóng các tất cả các đơn vị quân sự tiến công 
        while (p != nullptr){ 
            // Nếu là quân đội quân Giải phóng 
            if (isLiberation){
                if (calDistance(p->unit-> getCurrentPosition(),pos)<= 2){
                //Thiết lập chỉ số chiến tranh AttackScore cho các đơn vị quân sự bị trừ 20% 
                double res =(double)(0.8*(p->unit->getAttackScoreDuringFight()));
                p->unit->setAttackScore(safeCeil(res));
                }    
            } else {
                // Nếu là quân đôi cộng hòa ARVN các đợn vị quân sự này đc cộng thêm 20% 
                if (calDistance(p->unit-> getCurrentPosition(),pos)<= 2){
                    double res = (double)(1.2* (p->unit->getAttackScoreDuringFight()));
                    p->unit->setAttackScore(safeCeil(res));
                }
            }
            p = p -> next;
        }
}
Fortification::~Fortification(){}

// SpecialZone: stub – các đơn vị trong bán kính 1 đơn vị có attackScore = 0
void SpecialZone::getEffect(Army *army) {
    if (!army || ! army -> getUnitList()) return;
    for (UnitList:: Node * p = army -> getUnitList() -> getHead(); p; p= p-> next){
        Unit* u = p-> unit;
        if (calDistance(p-> unit-> getCurrentPosition(),pos) <= 1.0){
            u-> setAttackScore(0); // Thiết lập tất cả đơn vị quân sự nằm trong bán kính 1 đơn vị 
        }
        }
}
SpecialZone::~SpecialZone(){}
//!-----------------------------------------------------
//! CLASS BattleField
//!-----------------------------------------------------
BattleField::BattleField(int n_rows, int n_cols, const vector<Position*>& arrayForest,
                         const vector<Position*>& arrayRiver, const vector<Position*>& arrayFortification,
                         const vector<Position*>& arrayUrban, const vector<Position*>& arraySpecialZone)
    : n_rows(n_rows), n_cols(n_cols)
{
    if (this->n_rows <=0 || this -> n_cols <=0){
        terrain = nullptr;
        this -> n_rows =0;
        this -> n_cols =0;
        return;
    }
    terrain = new TerrainElement**[n_rows];
    for (int i=0; i< n_rows;i++){
        terrain[i] = new TerrainElement *[n_cols];
        // Khởi tạo giá trị ban đầu cho ma trạn 
        for (int j= 0;j<n_cols;j++){
            terrain[i][j] =  nullptr;
        }
    }
   attachTerrainEffect(arrayForest, Location:: forest);
   attachTerrainEffect(arrayRiver, Location:: river);
   attachTerrainEffect(arrayFortification, Location:: fortification);
   attachTerrainEffect(arrayUrban, Location:: urban);
   attachTerrainEffect(arraySpecialZone, Location:: SpecialArea);
   // Ngoài các yêu tố trong mảng trên đều lsf đường mòn
   for (int i=0;i<n_rows;i++){
        for (int j=0;j<n_cols;j++){
            if (terrain[i][j] == nullptr) terrain[i][j] = new Road(Position(i,j));
        }
   }
}

BattleField::~BattleField() {
    if (!terrain) return;
    // Nếu terrain đã là nullptr thì ko cần xóa 
    for (int i=0;i<n_rows;i++){
        for (int j=0;j<n_cols;j++){
            delete terrain [i][j];
        }
        delete [] terrain[i];
    }
    delete [] terrain; //Xóa các mục terrain 
}

TerrainElement* BattleField::getElement(int r, int c) const {
        // Kiểm tra nếu ko  nằm trong tiền tuyến chiến đấu
        if (! isInsideMap(r,c)) return nullptr;
        return terrain[r][c]; // Lây vị trí của r và c trỏ đễn con trỏ thích hợp

}
// Kiểm tra xem nhân tố có nằm trên bản đồ hay không 
bool BattleField:: isInsideMap(int row, int col) const{
        return (row>= 0 && col>=0 && row <this ->n_rows && col < this-> n_cols);
}

string BattleField::str() const {
    stringstream ss;
    ss<<"BattleField[n_rows="<< n_rows <<",n_cols="<< n_cols <<"]";
    return ss.str();
}
void BattleField::attachTerrainEffect (const vector <Position*> & positions,Location type){
    for (Position* pos : positions){
        int row = pos-> getRow();
        int col = pos -> getCol();
        if (!isInsideMap(row,col)   || terrain [row][col]  != nullptr) continue;
        switch (type){
            case Location :: forest : terrain [row][col] = new Mountain(*pos);
            break;
            case Location::river: terrain [row][col] = new River(*pos);
            break;
            case Location :: fortification: terrain [row][col] = new Fortification(*pos);
            break;
            case Location:: urban: terrain[row][col] = new Urban(*pos);
            break;
            case Location:: SpecialArea: terrain [row][col] = new SpecialZone(*pos);
            break;
            default: break;
        }
    }
}
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
string Configuration ::trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
string Configuration:: deleteSpace(const string &s){
    string res="";
    for (char c:s){ // Duyết mảng ký tự bằng chuỗi for _each based
        if (c != ' ') res += c;
    }
    return res;
}

Configuration::Configuration(const std::string &filepath) {     // viết chương trình mở file thích hợp 
    LibertyUnitNum =0;
    ARVNUnitNum =0;
    fstream inFile(filepath);
    if (!inFile.is_open()) return;
   
    string field [6];   
    const string key []= {"ARRAY_FOREST","ARRAY_RIVER","ARRAY_FORTIFICATION", "ARRAY_URBAN","ARRAY_SPECIAL_ZONE","UNIT_LIST"};
    bool check[]={ false,false,false,false,false,false,false};// Khai báo 6 phần tử đều mang giá trị false
    string s [] ={"","","","","",""};  // Gán chuỗi s hiện có này là chuỗi rỗng 
    vector <Unit*> liberty, arvn;  // Đọc các thông số của các đơn vị cộng hòa cùng với các đơn vị giải phóng 
    // ý  tưởng đọc các dòng lấy các chỉ số định nghĩa ở mỗ dòng đọc đến dâu = sau đó lấy tín hiệu chữ cái
    // Dùng switch để lấy các đối số tương ứng cho đối tượng
   
    string line;
while (getline(inFile, line)) {
    line = trim(line);
    line = deleteSpace(line);
    if (line.empty()) continue;

    size_t posEqual = line.find('=');
    if (posEqual == string::npos) continue;

    string keyWord = line.substr(0, posEqual);
    string valueStr = line.substr(posEqual + 1);
    int val = 0;
    stringstream ss(valueStr);
    ss >> val;

    // Xác định giá trị switch
    bool matched = true;
    InforInput checkFigure;

    if (keyWord == "NUM_ROWS") {
        checkFigure = InforInput::NUM_ROWS;
    } else if (keyWord == "NUM_COLS") {
        checkFigure = InforInput::NUM_COLS;
    } else if (keyWord == "EVENT_CODE") {
        checkFigure = InforInput::EVENT_CODE;
    } else {
        matched = false;
    }

    // Xử lý bằng switch-case nếu hợp lệ
    if (matched) {
        switch (checkFigure) {
            case InforInput::NUM_ROWS:
                this->num_rows = val;
                break;
            case InforInput::NUM_COLS:
                this->num_cols = val;
                break;
            case InforInput::EVENT_CODE:{
                if (val < 0) val= 0;
                else if(val >=100) val%=100;
                this->eventCode = val;
                break;
            }
            default:
                break;
        }
    }
        int i=0;
        while (i<6){
                // Nối tất cả các dòng còn array hoặc Unitlist lại với nhau
            mergeLine (line,s[i],key[i],check[i]);
            i++;
        }
    }
    inFile.close();  // Đóng File tập tin lại 
    // Đọc xử lý các tọa độ vị trí Vector cần thiết 
    
    readPositionVector(arrayForest,s[0]);
    readPositionVector(arrayRiver,s[1]);
    readPositionVector(arrayFortification,s[2]);
    readPositionVector(arrayUrban,s[3]);
    readPositionVector(arraySpecialZone,s[4]);
    // Dọc xử lý các đơn vị quân đội đầu vào 
    readUnitVector(liberty,arvn,s[5]);
    LibertyUnitNum = liberty.size();   // Lấy kích thước của chế đọ Giải phóng 
    ARVNUnitNum = arvn.size();     // Lấy kích thước đơn vị của quân Cộng Hòa 
    
    for (Unit* u : liberty) {
        this->liberationUnits.push_back(u);
    }
    for (Unit* u : arvn) {
        this->ARVNUnits.push_back(u);
    }



}

Configuration::~Configuration() {
    // Giải phóng các đối tượng Position đã được cấp phát
    releaseVector(arrayForest);
    releaseVector(arrayRiver);
    releaseVector(arrayFortification);
    releaseVector(arrayUrban);
    releaseVector(arraySpecialZone);
    releaseVector(liberationUnits);
    releaseVector(ARVNUnits);
}
// Hàm hỗ trợ in vị trí cá tọa độ thích hợp cho chiến địa 
string Configuration :: printPositionArray (vector<Position*> arrayPosition) const {
    if (arrayPosition.empty()) return "";
    stringstream oss;
    for (Position* position : arrayPosition){
        oss<< position -> str();
        oss<<",";   // In đầu, ở vị trí liền kề cần phải giải quyết việc xóa đối  
    }
    return (oss.str()).substr(0, (oss.str()).length()-1);     // Loại bớt một đấu , cuối ra khỏi chuỗi 
}
string Configuration::str() const {  // Lưu ý từ một đối tượng const theo thì cần phải gọi các phương thức const 
    stringstream ss;
    ss<<"[num_rows="<<this-> num_rows;
    ss<<",num_cols="<<this -> num_cols;
    ss<<",arrayForest=["<< printPositionArray (arrayForest)  <<"]";
    ss<<",arrayRiver=["<<  printPositionArray  (arrayRiver)  <<"]";
    ss<<",arrayFortification=["<< printPositionArray  (arrayFortification) <<"]" ;
    ss<<",arrayUrban=["<< printPositionArray  (arrayUrban) <<"]" ;
    ss<<",arraySpecialZone=["<< printPositionArray  (arraySpecialZone)  <<"]"  ;
    // ss<<",liberationUnits=[" << printUnitArr(liberationUnits,LibertyUnitNum)<<"]";  // Trưng dụng các đơn vị liberation ra bên ngoài
    // ss<<",ARVNUnits=["<< printUnitArr(ARVNUnits,ARVNUnitNum)<<"]";
    ss << ",liberationUnits=[" << printUnitArr(liberationUnits) << "]";
    // cout<< printUnitArr(liberationUnits)<<endl;
    ss << ",ARVNUnits=[" << printUnitArr(ARVNUnits) << "]";
    // cout<< printUnitArr(ARVNUnits) <<endl;

    ss<<",eventCode="<<this-> eventCode<<"]";
    // ss<<"]";
    return ss.str();
}

string Configuration::printUnitArr(vector<Unit*> unitArr) const {
    if (unitArr.empty()) return "";
    stringstream ss;
    for (size_t i = 0; i < unitArr.size(); i++) {
        ss << unitArr[i]->str();
        if (i != unitArr.size() - 1) ss << ",";
    }
   
    return ss.str();
}
// Phương thưc dùng để xóa các taì nguyên vector 
void releaseVector (vector <Position*> &posArr){  // Xóa trực tiếp trên bản sao của nó luôn 
    if (posArr.empty()) return;
    for (Position* pos : posArr){
        delete pos;  // Giải phóng vùng nhớ heap
    }
    posArr.clear();   // Xóa ko gian vector đảm bảo
}
void releaseVector (vector<Unit*> &unitArr){
    if (unitArr.empty()) return;
    for (Unit* u : unitArr){
        delete u;  // Giải phóng vùng nhớ heap
    }
    unitArr.clear();   // Xóa ko gian vector đảm bảo
}

void Configuration :: mergeLine (string line,string &arrName,string key,bool &flag){
    if (line.find(key) != string::npos){
        arrName+=line;
        flag =(line.find("]") == string::npos);
    } else if (flag){
        arrName+=line;
        flag = (line.find("]")== string::npos);
    }
}

// Lưu ý cần phải viết thêm các hàm xử lý các chỉ số đơn vị Position 

void Configuration::readPositionVector(vector<Position*>& posArr, string& s) {
    size_t k = s.find('[');
    if (k == string::npos) return;  // Không tìm thấy dấu mở '[' → không đúng định dạng

    stringstream ss(s.substr(k + 1)); // Bắt đầu từ sau dấu '['
    char temp;
    int k1, k2;

    while (ss >> temp) {
        if (temp == '(') {
            if ((ss >> k1) && (ss >> temp) && temp == ',' && (ss >> k2) && (ss >> temp) && temp == ')') {
                posArr.push_back(new Position(k1, k2));
                if (ss.peek() == ',') ss.ignore();     // Bỏ dấu ',' nếu có
            } else {
                break;  // Nếu định dạng sai thì dừng luôn
            }
        } else if (temp == ']') {
            break;  // Kết thúc mảng
        }
    }
}


// Lưu ý cần phải viết thêm các hàm xử lý các đơn vị unit 
vector<string> Configuration::splitUnits(const string &block) {
   
    vector<string> result;
    int depth = 0;
    string token = "";

    for (char ch : block) {
        if (ch == '(') depth++;
        if (ch == ')') depth--;

        token += ch;

        if (ch == ')' && depth == 0) {
            result.push_back(token);
            token.clear();
        }
    }
    return result;
}
void Configuration::readUnitVector(vector<Unit*>& liberationUnits, vector<Unit*>& ARVNUnits, const string &s) {
   
    size_t pos = s.find("UNIT_LIST=[");
    if (pos == string::npos) return;

    size_t start = s.find('[', pos);
    size_t end = s.rfind(']');  // Sửa chỗ này để lấy toàn bộ block dù xuống dòng
    if (start == string::npos || end == string::npos || end <= start) return;
    string block = s.substr(start + 1, end - start - 1); // phần trong dấu []
    vector<string> tokens = splitUnits(block);

    for (string token : tokens) {
        
        while (!token.empty() && (token[0] == ',' || token[0] ==' ')) {
            token = token.substr(1);
        }
        size_t nameTail = token.find('(');
        if (nameTail == string::npos) continue;

        string unitName = token.substr(0, nameTail);
      
        string content = token.substr(nameTail + 1);
        if (!content.empty() && content.back() == ')') content.pop_back();

        int quantity, weight, row, col, unitBelong;

        // Tách thủ công từng thành phần
        size_t pos1 = content.find(',');
        size_t pos2 = content.find(',', pos1 + 1);
        size_t lParen = content.find('(', pos2 + 1);
        size_t commaInPos = content.find(',', lParen);
        size_t rParen = content.find(')', commaInPos);
        size_t lastComma = content.find(',', rParen);

        try {
            quantity = stoi(content.substr(0, pos1));
            weight = stoi(content.substr(pos1 + 1, pos2 - pos1 - 1));
            row = stoi(content.substr(lParen + 1, commaInPos - lParen - 1));
            col = stoi(content.substr(commaInPos + 1, rParen - commaInPos - 1));
            unitBelong = stoi(content.substr(rParen + 2));
        } catch (...) {
            cout << "Failed to parse: " << content << endl;
            continue;
        }
        

        Position p(row, col);
       
        Unit * u = nullptr;
         if (unitName == "TANK") {
            
            u = new Vehicle(quantity, weight, p, TANK);   // Có sự tham gia gán thành công ngay tại đơn vị này 
            
         }
        else if (unitName == "APC") u = new Vehicle(quantity, weight, p, APC);
        else if (unitName == "MORTAR") u = new Vehicle(quantity, weight, p, MORTAR);
        else if (unitName== "TRUCK") u = new Vehicle(quantity, weight, p, TRUCK);
        else if (unitName == "REGULARINFANTRY") {
            u = new Infantry(quantity, weight, p, REGULARINFANTRY);     // Có sự tham gia gán thành công ngay tại đơn vị này 
            
        }
        else if (unitName == "SNIPER") u = new Infantry(quantity, weight, p, SNIPER);
        else if (unitName == "ENGINEER") u = new Infantry(quantity, weight, p, ENGINEER);
        else if (unitName == "SPECIALFORCES") u = new Infantry(quantity, weight, p, SPECIALFORCES);
        else if (unitName == "ANTIAIRCRAFTSQUAD") u = new Infantry(quantity, weight, p, ANTIAIRCRAFTSQUAD);
        else if (unitName == "MORTARSQUAD") u = new Infantry(quantity, weight, p, MORTARSQUAD);
        //   UNIT_LIST=[TANK(5,2,(1,2),0),REGULARINFANTRY(5,2,(3,3),1)]
        if (u != nullptr) {
            u->setUnitBelong(unitBelong);
            if (unitBelong == 0) {
               
                liberationUnits.push_back(u);
               
            }
            else{
                
                ARVNUnits.push_back(u);

            }
        }
    }
}
  

bool Configuration::isInfantry (const string &name ){
     return name == "SNIPER" || name == "ANTIAIRCRAFTSQUAD" || name == "MORTARSQUAD" ||
           name == "ENGINEER" || name == "SPECIALFORCES" || name == "REGULARINFANTRY";

}
bool Configuration :: isVehicle (const string & name ){
     return (name == "TANK" || name == "TRUCK" || name == "MORTAR" || name == "ANTIAIRCRAFT" 
                    || name == "ARMOREDCAR" || name == "APC" || name == "ARTILLERY")  ;
}
///////////////////////////////////////////////////////////////////
/////                   HCM CAMPAIGN
/////
////////////////////////////////////////////////////////////////////
HCMCampaign::HCMCampaign ( const string & config_file_path ){
    config = new Configuration(config_file_path);
// Thiết lập các yếu tố cần thiết cho class 
/////////////////////////////////////////////
//          BATTLEFIELD FACTOR
//
//////////////////////////////////////////////
    int row = config -> getNumRows();
    int col = config -> getNumCols();
// vector<Position*> arrayForest = config -> getForestPositions();
// vector<Position*> arrayRiver = config -> getRiverPositions();
// vector<Position*> arrayFortification = config -> getForestPositions();
// vector<Position*> arrayUrban = config -> getUrbanPositions();
// vector<Position*> arraySpecialZone = config -> getSpecialZone();
    battleField= new BattleField (row,col, config -> getForestPositions(), config -> getRiverPositions(), 
                    config -> getFortificationPositions(), config -> getUrbanPositions(),  config -> getSpecialZonePositions());

//////////////////////////////////////////////////
//          Liberty+ ARVN Army 
//
/////////////////////////////////////////////////
// Idea : tạo 1 khung chung để thiết lập các đơn vị quân sự 
// Army ( Unit ** unitArray , int size , string name , BattleField *
// battleField );  - model để setup army
    vector<Unit*>& liberVector = config->getLiberationUnits();
    vector<Unit*>& arvnVector = config->getARVNUnits();
    LibertyUnitArray = new Unit*[liberVector.size()];
    ARVNUnitArray = new Unit*[arvnVector.size()];
    LibertyUnitArray = config -> getLiberationUnits();
    ARVNUnitArray = config -> getARVNUnits();
    // vector<Unit*> liberUnit (LibertyUnitArray, LibertyUnitArray+ (int) config -> getLibertyUnitNum()); // Chú ý có thể đưa ra ngoài vị trí 
    // vector <Unit*> arvnUnit (ARVNUnitArray ,ARVNUnitArray+ (int) config -> getARVNUnitNum());
    // // Khởi tạo đơn vị quân sự cho cho quân giải phóng 
    // initialArmy (Army* armyName,vector<Unit*> & unit , Unit** unitArray, bool isARVN)
     for (size_t i = 0; i < liberVector.size(); ++i)
        LibertyUnitArray[i] = liberVector[i];

    for (size_t i = 0; i < arvnVector.size(); ++i)
        ARVNUnitArray[i] = arvnVector[i];

     // Khởi tạo quân đội
    initialArmy(liberationArmy, liberVector, LibertyUnitArray, false);
    initialArmy(ARVNArmy, arvnVector, ARVNUnitArray, true);
}
     

void HCMCampaign:: run (){    // Các yếu tố quan sự bị ảnh hưởng bởi các yếu tố ĐỊA HÌNH trước rồi mới GIAO TRANH 
// Ap dung các phương thức địa hình trước rồi mới thâm chiến 
    getBattleEffect(liberationArmy);
    getBattleEffect (ARVNArmy);
// Xét các chỉ số quân sự khi đề cập đến EVENTCODE 
    int eventCode = config -> getEventCode();
    if (eventCode  >= 75){
    ARVNArmy -> fight (ARVNArmy,false);       // Quân đôi Sài Gòn tấn công 
    liberationArmy -> fight (liberationArmy,true);
    liberationArmy -> fight (liberationArmy,false);    // Quân đội Giai phòng tân công 
    ARVNArmy -> fight (ARVNArmy,true);   

    } else {
   // Quân Gỉai Phóng trong thế tấn công 
    liberationArmy -> fight (liberationArmy,false);
   // Quân Sài Gòn trong thế phòng thủ 
    ARVNArmy -> fight (ARVNArmy,true);   


}

// Gọi các hàm sau khi tham chiến  xảy ra 
 // GỌI lại các chỉ số quân sự sau chiến tranh xảy ra 
        // Phải update ở quân đội army Liber và ARVN xuất các chỉ số sau thma chiến 
    liberationArmy-> printAfterWar();
    ARVNArmy->printAfterWar();

}
string HCMCampaign::printResult(){
    //In ra các chỉ số LF và EXP sau giao tranh
    stringstream ss;
    ss<<"LIBERATIONARMY=[LF="<<  liberationArmy-> getLF()<<",EXP="<<  liberationArmy-> getEXP()<<"]";
    ss<<"-ARVN=[LF=" << ARVNArmy-> getLF()<<",EXP="<< ARVNArmy-> getEXP()<<"]";
    return ss.str();
}
// HCMCampaign::~HCMCampaign(){   // Thực hiện giải phóng các tài nguyên nếu cần thiết 
//     delete config;
//     delete battleField;
//     delete liberationArmy;
//     delete ARVN;
// }
HCMCampaign::~HCMCampaign() {
    delete config;
    delete battleField;
    delete ARVNArmy;
    delete liberationArmy;

    // Xóa mảng động tránh rò rỉ bộ nhớ
    delete[] LibertyUnitArray;
    delete[] ARVNUnitArray;
}
void HCMCampaign::getBattleEffect(Army *army ){
    int row = config->getNumRows();
    int col = config->getNumCols();

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            TerrainElement * terrain = battleField->getElement(r, c);  // Anh hương các chỉ số quân sự lên các yếu tố địa hình 
            if (terrain) terrain->getEffect(army);
        }
    }
}
void HCMCampaign:: initialArmy (Army* & armyName,<Unit*> & unit , Unit** &unitArray, bool isARVN){
    size_t total = unit.size();
    for (int i=0;i<total;i++){
        unitArray[i] = unit [i];
    }
    if (isARVN == true){
        this->ARVNArmy= new ARVN(unitArray,total,"ARVN Army", this -> battleField);
    } else {
        this->liberationArmy= new LiberationArmy(unitArray,total,"Liberation Army",this-> battleField);
    }
}