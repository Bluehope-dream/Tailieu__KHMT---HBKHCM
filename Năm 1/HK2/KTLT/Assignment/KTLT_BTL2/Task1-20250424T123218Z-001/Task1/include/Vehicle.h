#ifndef VEHICLE_H
#define VEHICLE_H

#include "Unit.h"

enum VehicleType
{
    TRUCK,
    MORTAR,
    ANTIAIRCRAFT,
    ARMOREDCAR,
    APC,
    ARTILLERY,
    TANK
};


class Vehicle : public Unit
{
    // TODO: implement
    private:
        VehicleType vehicleType;
    public:
    Vehicle (int quantity, int weight, const Position pos,VehicleType vehicleType);
    static string vehicleReflexion(const VehicleType &vehicleName);
    int getAttackScore() override ;
    string str() const override ;
};

#endif // VEHICLE_H
