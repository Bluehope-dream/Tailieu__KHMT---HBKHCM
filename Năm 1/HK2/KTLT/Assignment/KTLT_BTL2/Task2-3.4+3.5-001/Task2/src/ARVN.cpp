#include "ARVN.h"

// TODO: Implement
ARVN::ARVN(Unit** unitArray, int size, string name)
    : Army(unitArray, size, name) {
        // TODO: Implement
}
void ARVN::fight(Army* enemy, bool defense) {
    // TODO: Implement
    if (defense == false ){
        // Thể hiện sự tấn công của quân đội cộng hòa
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
        enemy->findMinestGreaterLiberArmy(setOfVehicle,setOfInfantry, A,B,enemy-> unitList,getLF(),getEXP());
            // Sự khó khăn và nhọc nhằn ở bài tập này là cần cập nhật cả về chỉ số sức mạnh và năng lực hiện tại của 
            // ta và kẻ thù 
        bool check =(!A.empty() && !B.empty() )|| (!A.empty() && safeCeil(1.5*enemy->getEXP())> EXP ) ||
                            (!B.empty() && safeCeil(1.5*enemy-> getLF()) > LF );
        if (check) upload(enemy -> unitList); // Cập nhật lại chỉ số thông tin unitList
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
    findLFEXP();
    setAttackScore();
    checkEXPrange(EXP);
    checkLFrange(LF);
}


string ARVN::str() const {
    // TODO: Implement
    stringstream ss;
    ss<<"ARVN[LF="<<LF;
    ss<<",EXP="<<EXP;
    ss<<",unitList="<<unitList-> str();
    // ss<<",battleField";
    // if (battleField) ss<<battleField -> str();
    ss<<"]";
    return ss.str();
}
ARVN :: ~ARVN(){}  // Tạo destructor rỗng cho phần khởi tạo
// Viết hàm cập nhật cho  vấn đề upload các chỉ số của đội quân chiến tranh cho quân đội cộng hòa 
void ARVN:: upload(UnitList* List){
    UnitList* LiberList = deepCopyUnitList(List); //Tạo hàm truy cập sâu vào đối tượng list trên 
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
    delete LiberList; // Giải phóng vùng nhớ HEAP đang đc cấp phát 
}