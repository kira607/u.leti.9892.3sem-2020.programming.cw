#ifndef COURSEWORK_TRUCK_BRAND_H
#define COURSEWORK_TRUCK_BRAND_H

#include <string>
#include <stdexcept>

enum class TruckBrand
{
    Volvo = 1,
    MercedesBenz = 2,
    Man = 3,
    Daf = 4,
    Scania = 5,
    Iveco = 6,
    Renault = 7,
    Nissan = 8,
    Tatra = 9,
    Mitsubishi = 10,
    NONE = 0
};

std::string str(TruckBrand truck_brand);

#endif //COURSEWORK_TRUCK_BRAND_H
