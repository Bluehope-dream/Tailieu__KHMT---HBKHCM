#ifndef UNIT_H
#define UNIT_H

#include "Position.h"

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    Unit(int quantity, int weight, Position pos);
    virtual ~Unit();
    virtual int getAttackScore() = 0;
    Position getCurrentPosition() const;
    virtual string str() const = 0;
    // Dùng bộ đôi getter và setter để thay đổi dữ liệu đóng gói enscuplation  của chương trình 
    void setquantity(int );
    int getquantity();
    int getWeight();
    void setWeight(int weight);
};

#endif // UNIT_H
