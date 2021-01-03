#ifndef COURSEWORK_DRIVER_H
#define COURSEWORK_DRIVER_H

#include "../../common/truck_brand.h"

struct Driver
{
    int id;
    std::string surname;
    std::string name;
    std::string patronymic;
    TruckBrand truck_brand;

    Driver *prev;
    Driver *next;

    Driver();
    Driver(const Driver &driver);
};

#endif //COURSEWORK_DRIVER_H
