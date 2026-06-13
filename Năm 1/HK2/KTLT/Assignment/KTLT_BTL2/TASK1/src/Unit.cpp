#include "../include/Unit.h"

Unit::Unit(int quantity, int weight, Position pos)
{
    // TODO: implement
    this -> quantity =quantity;
    this -> weight =weight ;
    this ->pos =pos;
}

Unit::~Unit()
{
    // TODO: implement
    

}

Position Unit::getCurrentPosition() const
{
    return pos;
}
void Unit::setquantity(int &num){
    quantity = num;
}
int Unit::getquantity(){ return quantity;   }  // Vơi mục đích thiết lập lại quantity cho đôi tượng 
int Unit::getWeight(){ return weight;}
void Unit::setWeight(int weight){this->weight =weight;}