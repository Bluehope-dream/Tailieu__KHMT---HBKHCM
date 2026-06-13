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
        bool checkCommando (InfantryType &value, int &weight);
        int getPersonalIndex(int &score);
        string InfantryName (const InfantryType& value) const  ;
        int safeCeil(double val) ;
        bool isPerfect(int val);
};

#endif // INFANTRY_H