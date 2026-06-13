#ifndef INFANTRY_H
#define INFANTRY_H

#include "Unit.h"

enum InfantryType
{
    SNIPER,
    ANTIAIRCRAFTSQUAD,
    MORTARSQUAD,
    ENGINEER,
    SPECIALFORCES,
    REGULARINFANTRY
};

class Infantry : public Unit
{
    // TODO: implement
    private:
        InfantryType infantryType;
    public:
        Infantry(int quantity, int weight, const Position pos, InfantryType infantryType);
        int getAttackScore() override ;
        string str() const override ;
        bool checkCommando (InfantryType &value, int &weight);  // Hàm kiểm tra hàm điệp viên xét lấy score trong trường hợp đặc biệt 
        int getPersonalIndex(int &score);
        string InfantryName (const InfantryType& value) const  ;
        // int getScore ()const  override;
        int checkValue() override ;  // Hàm kiểm tra đầu vào  của dữ liệu
        int safeCeil(double val) ;
        bool isPerfect(int val);
};

#endif // INFANTRY_H