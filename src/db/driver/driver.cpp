#include "driver.h"

Driver::Driver()
{
    id = -1;
    surname = "NONE";
    name = "NONE";
    patronymic = "NONE";
    truck_brand = TruckBrand::NONE;

    prev = nullptr;
    next = nullptr;
}

Driver::Driver(const Driver &driver)
{
    id = driver.id;
    surname = driver.surname;
    name = driver.name;
    patronymic = driver.patronymic;
    truck_brand = driver.truck_brand;

    prev = nullptr;
    next = nullptr;
}
