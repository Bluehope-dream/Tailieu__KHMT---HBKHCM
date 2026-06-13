#include "LiberationArmy.h"

// TODO: Implement
// class LiberationArmy
LiberationArmy::LiberationArmy(Unit **unitArray, int size, string name)
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
        eraseInvalidCombo(A);
        eraseInvalidCombo(B);
        int numA = unitList-> getcountVehicle()-A.size();
        int numB = unitList->getcountInfantry() - B.size();
        unitList -> setcountVehicle(numA);
        unitList -> setcountInfantry(numB);
        champion = true;
        // Cập nhật phương thức truy cập kịp thời cho các thông tin về chỉ số 
        upload(enemy -> unitList);
        enemy -> setAttackScore(); // Cập nhật lại chỉ số chiến đấu AttackScore cho kẻ thù 
        enemy -> findLFEXP(); // Cập nhật lại chỉ số cho LF và EXP cho kẻ thù enemy 
                        
    } else if (! A.empty()&& safeCeil (1.5*EXP) > enemy -> getEXP() ){
        // xÉT CÁC CHỈ SỐ CỦA ĐỐI PHƯƠNG CHIẾN ĐẤU
        eraseInvalidCombo(A);
        eraseInvalidCombo(setOfInfantry);
        unitList -> setcountVehicle(unitList -> getcountVehicle()-A.size());
        unitList -> setcountInfantry(0);
        champion = true; // Quân đội ra sức chiến thắng 
        // Cập nhật lại kịp thời các thông số sau khi giao tranh xảy ra 
        upload(enemy -> unitList);
        enemy -> setAttackScore();
        enemy -> findLFEXP();
        // cout<<"Hello "<< getEXP();
    }
    else if  (! B.empty()&& safeCeil (1.5*LF) > enemy -> getLF() ){
    // xÉT CHỈ SỐ CHIẾN ĐẤU LF của đối phương 

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
    }
    else if (A.empty()&& B.empty()){
        // Xảy ra phương thức hòa hoãn 
        skipBattle = true; // Thể hiện  trạng thái ko giao tranh 
    }
    if (champion){
        // Nếu chiến thắng 
        // Cập nhật lại các chỉ số chiến tranh AttackScore , và LF, EXP
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
            LF = safeCeil(1.3*LF);
            EXP = safeCeil (1.3*EXP);
            checkEXPrange(EXP);
            checkLFrange(LF);
        }
        if ( LF >= enemy -> getLF() && EXP >= enemy -> getEXP())  return;
    }
        for (UnitList :: Node *p = unitList -> getHead();p; p=p-> next){
            Unit*u = p-> unit;
            u-> setquantity(safeCeil(u-> getquantity()*0.9));
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
    ss<<",unitList="<<unitList-> str()<<"]";
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