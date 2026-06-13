#include "../include/Army.h"
#include "../include/BattleField.h"

Army::Army(Unit** unitArray, int size, string name,BattleField* battleField) : name(name)
{
    // TODO: Implement
    if (size == 0) {
        LF = 0;
        EXP = 0;
        unitList = new UnitList(0);
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
        unitList = new UnitList(sum);
        for (int i = 0; i < size; i++) {
            unitList->insert(unitArray[i]);
            //  cout<<"LF "<<getLF()<<"EXP "<< getEXP();

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

// void Army::updateScore(bool update){
//     // TODO: Implement
// }
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
