#ifndef UNIT_H
#define UNIT_H

#include "Position.h"

class Unit
{
protected:
    int quantity, weight;
    Position pos;

public:
    int attackScore ; // thực hiện lấy chỉ số chiến đấu 
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
    // virtual int getScore() const = 0;
    // Lập hàm setPosition và getPosition Bộ getPosition này đã được biểu diễn tương đương với bộ Position getCurrentPosition   
    void setPos(Position pos);
    // Position getPos();
    
    virtual int checkValue()=0;// Thực hàm hàm kiểu dữ liệu kiểm tra xem kiểu dữ liệu đầu vào là Infantry hay là Vehicle 
};

#endif // UNIT_H
