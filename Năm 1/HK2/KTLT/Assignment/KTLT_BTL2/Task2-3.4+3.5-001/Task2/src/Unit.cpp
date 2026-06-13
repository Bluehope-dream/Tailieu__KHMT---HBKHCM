#include "../include/Unit.h"

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
// Position Unit::getPos(){  return pos;     } 