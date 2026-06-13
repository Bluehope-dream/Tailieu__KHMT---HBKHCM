#include "../include/Vehicle.h"

// TODO: implement
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
    return vehicleType;  // Truy xuất vehicleType để kiểm tra dữ liệu có phải là Vehicle hay không?
}
