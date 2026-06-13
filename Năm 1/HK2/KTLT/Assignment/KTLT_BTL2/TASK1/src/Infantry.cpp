#include "../include/Infantry.h"

// TODO: implement
Infantry::Infantry(int quantity, int weight, const Position pos, InfantryType infantryType): Unit(quantity,weight,pos),infantryType(infantryType) {}
int Infantry::getAttackScore()  {
      int base = static_cast<int> (infantryType) *56 +quantity*weight;
      if ( checkCommando (infantryType,weight)){
        return (base+=75);
      } 
      // Điều chỉnh các thuộc tính quantity và tính lại score
      int personal=getPersonalIndex(base);
      if (personal >7){
        quantity += ceil(0.2*quantity);
        setquantity(quantity);
        base = static_cast<int> (infantryType) *56 +quantity*weight;
      } else if (personal<3 ){
        if (0.1*quantity >=1){
        quantity-=ceil(0.1*quantity);
        setquantity(quantity);
        base = static_cast<int> (infantryType) *56 +quantity*weight;
        }
      }
   return base ;
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
    if (sqrt (weight)*sqrt(weight)== weight ) return true;
    return false;
}
int Infantry::getPersonalIndex(int &score){
    // Hàm tính tổng các chữ số của một năm 
    int sum=0, year=1975;
    while (year>0){
        sum += year %10;
        year /=10;
    }
    int tempo = score;
    while (tempo>0){
        sum+= tempo%10;
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
