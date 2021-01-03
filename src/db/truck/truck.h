#ifndef COURSEWORK_TRUCK_H
#define COURSEWORK_TRUCK_H

#include "../../common/truck_brand.h"

struct Truck
{
    int id;
    float capacity;
    int transportation_distance;
    TruckBrand brand;

    Truck *prev;
    Truck *next;

    Truck();
    Truck(const Truck &truck);
};

#endif //COURSEWORK_TRUCK_H
