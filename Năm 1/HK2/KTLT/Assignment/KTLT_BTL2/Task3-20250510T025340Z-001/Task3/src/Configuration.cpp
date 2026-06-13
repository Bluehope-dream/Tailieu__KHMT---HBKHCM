#include "Configuration.h"
//!-----------------------------------------------------
//! CLASS Configuration
//!-----------------------------------------------------
// * Hint: Bạn có thể thêm hoặc thay thế các phương thức khác để truy cập các thành viên riêng tư nếu cần thiết.
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
// Configuration::InforInput Configuration::mapkey(const string &infor){
//     if (infor == "NUM_ROWS") return  InforInput::NUM_ROWS;
//     else if (infor ==  "NUM_COLS") return InforInput::NUM_COLS;
//     else if (infor == "EVENT_CODE") return InforInput::EVENT_CODE;
//     else if (infor == "ARRAY_FOREST") return InforInput::ARRAY_FOREST;
//     else if (infor == "ARRAY_RIVER") return InforInput::ARRAY_RIVER;
//     else if (infor == "ARRAY_FORTIFICATION") return InforInput::ARRAY_FORTIFICATION;
//     else if (infor == "ARRAY_SPECIAL_ZONE") return InforInput::ARRAY_SPECIAL_ZONE;
//     else if (infor == "ARRAY_URBAN") return  InforInput::ARRAY_URBAN;
//     else if (infor == "UNIT_LIST")  return InforInput::UNIT_LIST;
//     return;
// }
Configuration::Configuration(const std::string &filepath): num_rows(0), num_cols(0) {     // viết chương trình mở file thích hợp 
    LibertyUnitNum =0;
    ARVNUnitNum =0;
    fstream inFile(filepath);
    if (!inFile.is_open()) return;
   
    string field [6];   
    const string key []= {"ARRAY_FOREST","ARRAY_RIVER","ARRAY_FORTIFICATION","ARRAY_SPECIAL_ZONE", "ARRAY_URBAN","UNIT_LIST"};
    bool check[]={ false,false,false,false,false,false,false};// Khai báo 6 phần tử đều mang giá trị false
    string s [] ={"","","","","",""};  // Gán chuỗi s hiện có này là chuỗi rỗng 
    vector <Unit*> liberty, arvn;  // Đọc các thông số của các đơn vị cộng hòa cùng với các đơn vị giải phóng 
    // ý  tưởng đọc các dòng lấy các chỉ số định nghĩa ở mỗ dòng đọc đến dâu = sau đó lấy tín hiệu chữ cái
    // Dùng switch để lấy các đối số tương ứng cho đối tượng
    string line;
    
    while (getline(inFile,line)){
        // Lưu ý do sự đảo lộn các vị trí thông tin nên các dòng sẽ có thể chứa các khoảng thừa khoảng trắng 
        // Do đó cần xử lý loại bỏ các khoảng thừa đó để đọc dữ liệu 
        // Đọc đến dấu = rồi dừng 
        line = trim(line);      // Loại bỏ khoảng trẳng đầu và khoảng trắng cuối cho phù hợp để đọc các thông số cho chính xác 
        line = deleteSpace(line);   // Tiếp tục loại bỏ khoảng trắng giữa các dòng 
        // stringstream ss(line);
        // getline(ss,checkFigure,'=');
        // Với những cách đọc dữ liệu đơn giản  như NUM_ROWS, NUM_COLS,EVENT_CODE thì có thể dùng các lệnh switch đơn giản như vậy
        InforInput checkFigure;
        if(line.find("NUM_ROWS") != string::npos) checkFigure = Configuration::InforInput::NUM_ROWS;
        else if (line.find("NUM_COLS") != string:: npos) checkFigure = Configuration::InforInput::NUM_COLS;
        else if (line.find("EVENT_CODE") != string:: npos) checkFigure = Configuration:: InforInput:: EVENT_CODE;
        // else if (line.find("ARVNUnits") != string::npos) checkFigure = Configuration:: InforInput:: EVENT_CODE;
        switch(checkFigure) {
            case(Configuration::InforInput::NUM_ROWS):
            // Đọc tiếp đến vị trí tiếp theo để lấy giá trị cho những thông số cơ bản
            case(Configuration::InforInput::NUM_COLS):
            case(Configuration::InforInput::EVENT_CODE):
            {   
                string tempo =line;
                size_t m = tempo.find("=");
                tempo = tempo.substr(m+1,tempo.length() - m);   // Đọc lấy vị trí của thông số cơ bản 
                stringstream ss(tempo);
                int val=0;
                ss>> val;  // Đọc lấy giá trị 
                if (checkFigure == Configuration::InforInput::NUM_ROWS)  this -> num_rows = val;
                else if (checkFigure == Configuration::InforInput::NUM_COLS) this -> num_cols = val;
                else if (checkFigure == Configuration::InforInput::EVENT_CODE){
                    eventCode = val;
                    if (eventCode <0) this -> eventCode =0;
                    else if (eventCode >= 100) this -> eventCode %=100; // Lấy 2 chữ số cuối cung cho đối tượng 

                }    
            break;
            }
            
            default: 
            // Bắt đầu xử lý các dong không array hoặc unitlist 
            // Đã đọc xong các thông tin cơ bản bắt đầu xử lý các ARRAY_x và unitlist cần phải thiết kế
            // Có thể các thông tin cơ bản sẽ nằm trên đa dòng nên cần phải đưa về 1 dòng 
            int i=0;
            while (i<6){
                // Nối tất cả các dòng còn array hoặc Unitlist lại với nhau
                mergeLine (line,s[i],key[i],check[i]);
                i++;
            }
            break;
        }
    }
    inFile.close();  // Đóng File tập tin lại 
    // Đọc xử lý các tọa độ vị trí Vector cần thiết 
    readPositionVector(arrayForest,field[0]);
    readPositionVector(arrayRiver,field[1]);
    readPositionVector(arrayFortification,field[2]);
    readPositionVector(arrayUrban,field[3]);
    readPositionVector(arraySpecialZone,field[4]);
    // Dọc xử lý các đơn vị quân đội đầu vào 
    readUnitVector(liberty,arvn,field[5]);
    LibertyUnitNum = liberty.size();   // Lấy kích thước của chế đọ Giải phóng 
    ARVNUnitNum = arvn.size();     // Lấy kích thước đơn vị của quân Cộng Hòa 
    // Khai báo vector<Unit*> liberationUnits, ARVNunits,liberty,arvn,
    // Có cần phải cấp phát vector như con trỏ 2 chiều ko ví dụ nhiw liberationUnits = new Unit * [this-> LibertyUnitNum];
    for (int i=0;i<this->LibertyUnitNum;i++){
        this -> liberationUnits [i] = liberty [i];  // Nó đã là một mảng động ko cần cấp phát như những con trỏ khác đâu 
    }
    for (int i =0;i< this -> ARVNUnitNum;i++){
         this -> ARVNUnits [i] = arvn[i];
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
    // ss<<"Configuration[\n";
// "[num_rows=12,num_cols=12,arrayForest=[(1,1),(2,2)],
// arrayRiver=[(7,7)],arrayFortification=[(6,6)],arrayUrban=[(3,3),(4,4)],arraySpecialZone=[(5,5)],
// liberationUnits=[],ARVNUnits=[],eventCode=99]";
    ss<<"[num_rows="<<this-> num_rows;
    ss<<",num_cols="<<this -> num_cols;
    ss<<",arrayForest=["<< printPositionArray (arrayForest)  <<"]";
    ss<<",arrayRiver=["<<  printPositionArray  (arrayRiver)  <<"]";
    ss<<",arrayFortification=["<< printPositionArray  (arrayFortification) <<"]" ;
    ss<<",arrayUrban=["<< printPositionArray  (arrayUrban) <<"]" ;
    ss<<",arraySpecialZone=["<< printPositionArray  (arraySpecialZone)  <<"]"  ;
    ss<<",liberationUnits=[" << printUnitArr(liberationUnits,LibertyUnitNum)<<"]";  // Trưng dụng các đơn vị liberation ra bên ngoài
    ss<<",ARVNUNITS=["<< printUnitArr(ARVNUnits,ARVNUnitNum)<<"]";
    ss<<",eventCode="<<this-> eventCode<<"]";
    // ss<<"]";
    return ss.str();
}
// Cần phải viết một string Unit để in ra các chuỗi Unit thích hợp
 string Configuration:: printUnitArr(vector<Unit*> unitArr, int size ) const {
    if (size == 0) return"";
    stringstream ss;
    for (int i=0;i<size;i++){
        ss<< unitArr[i] -> str();
        if ( i != size -1) ss<<",";   
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
// Trong một số trường hợp các thông số nằm ở nhiều dòng khác nhau 
// Ví dụ: khi arrayForest =[
// (1,2),(3,5),
// (4,8)
// ] chứa nhiều dòng nên phải gọp dòng lại
void Configuration :: mergeLine (string line,string &arrName,string key,bool &flag){
    if (line.find(key) != string::npos){
        arrName+=line;
        flag =(line.find("]") == string::npos);
    } else if (flag){
        arrName+=line;
        flag = (line.find("]")== string::npos);
    }
}
int Configuration ::getUnitType(string name){
    string infantryName[] ={"SNIPER", "ANTIAIRCRAFTSQUAD", "MORTARSQUAD", "ENGINEER", "SPECIALFORCES", "REGULARINFANTRY"};
    string vehicleName[] = {"TRUCK", "MORTAR", "ANTIAIRCRAFT", "ARMOREDCAR", "APC", "ARTILLERY", "TANK"};
    for (int i=0;i<6;i++){
        if (name == infantryName[i] || name == vehicleName[i]) return i; // Lấy vị trí ánh xạ ra đơn vị thích hợp
    }
    return 6;   //Lấy ra đơn vị TANK thích hợp 
}
// Lưu ý cần phải viết thêm các hàm xử lý các chỉ số đơn vị Position 
void Configuration ::readPositionVector(vector<Position*>& posArr, string &s){
    size_t k = s.find('(');
    if (k == string :: npos) return; // Nếu ko đúng định dạng lập tức thoát 
    stringstream ss(s.substr(k)); // Đọc chuỗi vào ss từ vị trí thứ k
    char temp;
    int k1,k2;
    while (ss >> temp && temp == '('){  // Đọc từng cặp (x,y) thích hợp
        if (!(ss>>k1)) break;    // Đọc được giá trị k1
        if (!(ss>>temp) || temp !=',') break;
        if (!(ss>>k2)) break;    // Nếu ko đọc được giá trị k2 fail 
        if (!(ss>>temp) || temp != ')') break;
        posArr.push_back(new Position(k1,k2));   // Thêm vào mảng các vị trí Pos mới vào mảng 
    }
}

// Lưu ý cần phải viết thêm các hàm xử lý các đơn vị unit 
void Configuration :: readUnitVector(vector<Unit*>& libertyUnits, vector<Unit*>& ARVNUnits, const string &s){
    size_t pos = s.find("UNIT_LIST=[");
    if (pos == string::npos) return;
    size_t start = s.find('[',pos);  // Kiếm vị trí xuất hiện của kí tự [ kể tù vị trí pos 
    size_t end = s.find(']',start); // Tìm kiếm vị trí của dấu ] kể từ vị trí start 
    if (start == string::npos|| end == string::npos) return;      // Tìm kiếm xem vị trí bắt đầu và kết thúc của khói đọc block bên trong hay không 
    string blockUnit = s.substr(start+1,end-start -1);    // Chỉ lấy phần bên trong dấu [    ] đọc các thông tin dữ liệu
    while (!blockUnit.empty()){  // Kiểm tra xem dữ liệu trong khối 
        size_t unitTail = blockUnit.find(')');
        if (unitTail == string::npos) break;
        size_t nameTail = blockUnit.find('(');
        string unitName = blockUnit.substr(0,nameTail);  // Đọc được UNITNAME nằm trong khối đã cho 
        string content = blockUnit.substr(nameTail+1,unitTail - nameTail -1);  // Đọc nội dung chứa bên trong khối block cần để viết giá trị 
        int quantity,weight,row,col, unitBelong ;
        char skip;
        // Đọc dữ liệu stringstream cho nội dung này 
        stringstream ss(content);
        ss>> quantity>> skip >> weight >> skip >> skip>>row>> skip >> col >>skip >> unitBelong;
        Position p (row,col);
        if (unitBelong == 0){
            // LiberArmy Quân đội Giải Phóng 
            if (isInfantry(unitName)){
                liberationUnits.push_back(new Infantry(quantity,weight,p,(InfantryType) getUnitType(unitName)));
            } else if (isVehicle(unitName)){
                liberationUnits.push_back(new Vehicle (quantity,weight,p,(VehicleType) getUnitType(unitName)));
            }
        } else {
            // ARVN Quân đội cộng hòa 
             if (isInfantry(unitName)){
                ARVNUnits.push_back(new Infantry(quantity,weight,p,(InfantryType) getUnitType(unitName)));
             } else if (isVehicle(unitName)){
                ARVNUnits.push_back(new Vehicle(quantity,weight,p,(VehicleType)getUnitType(unitName)));
            }
        }
        // Cắt chuỗi cho vòng lặp tiếp theo 
        size_t nextStart = blockUnit.find(',', unitTail +1);
        if (nextStart == string::npos) break;
        blockUnit = blockUnit.substr(nextStart +1);
        blockUnit = trim (blockUnit);  // Cần phải loại bỏ các khoảng trắng nằm bên ngoài khối block để xử lý thông tin 
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