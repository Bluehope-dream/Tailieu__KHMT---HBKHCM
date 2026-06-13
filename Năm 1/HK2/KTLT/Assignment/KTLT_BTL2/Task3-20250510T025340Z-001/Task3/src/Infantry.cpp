#include "../include/Infantry.h"

// TODO: implement
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
// int Infantry::getAttackScore()  {
//       int base = static_cast<int> (infantryType) *56 +quantity*weight;
//       if ( checkCommando (infantryType,weight)){    // Điều kiện kiểm tra thử hàm này phải là hàm điệp viên đặc biệt hay ko
//         return (base+=75);
//       } 
//       // Điều chỉnh các thuộc tính quantity và tính lại score
//       int personal=getPersonalIndex(base);
//       if (personal >7){
//         double res = (double) quantity *6.0/5.0;
//         this-> quantity = safeCeil(res);
//         if (this-> quantity <1) this-> quantity =1;
        
//       } else if (personal<3 ){
//         double res = double (quantity) *0.9;
//         this-> quantity= safeCeil(res);
//         if (this-> quantity <1) this-> quantity =1;
       
//       }
//       base = static_cast<int> (infantryType) *56 +quantity*weight;
//    return base ;
// } 
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
