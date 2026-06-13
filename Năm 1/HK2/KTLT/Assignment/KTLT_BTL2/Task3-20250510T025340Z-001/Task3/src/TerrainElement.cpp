#include "TerrainElement.h"
#include "LiberationArmy.h"
#include"ARVN.h"

//!-----------------------------------------------------
//! Lớp TerrainElement và các lớp dẫn xuất
//!-----------------------------------------------------
class LiberationArmy;
class ARVN;
// Constructor và Destructor của TerrainElement
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
    } else if (dynamic_cast<ARVN*>(army)){
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