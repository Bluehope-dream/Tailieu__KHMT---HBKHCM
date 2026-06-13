#include "../include/Vehicle.h"

// TODO: implement
Vehicle::Vehicle (int quantity, int weight, const Position pos,VehicleType
    vehicleType):
        Unit(quantity, weight,pos),
        vehicleType (vehicleType){}

int Vehicle :: getAttackScore () {
    double result = (static_cast<int> (vehicleType) * 304 + quantity * weight)/30.0;  // đảm bảo tính an toàn là một số nguyên khi thực hiện phép toán 
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
     // Viết dòng lệnh in ra màn hình theo cú phá[p model cho sẵn 
     ss<<"Vehicle[";
     ss<<"vehicleType="<<vehicleReflexion(vehicleType)<<',';
     ss<<"quantity="<<quantity<<',';
     ss<<"weight="<<weight<<',';
     ss<<"position="<<pos.str()<<']';
     return ss.str();
} 