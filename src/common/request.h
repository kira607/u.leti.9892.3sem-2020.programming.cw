#ifndef COURSEWORK_REQUEST_H
#define COURSEWORK_REQUEST_H

#include "destination.h"
#include "truck_brand.h"
#include "date.h"
#include "../db/route/route.h"

struct Request
{
    float cargo_weight{};
    Date departure_date{};
    Date arrival_date{};
    Route *target_route{};
    Destination destination = Destination::NONE;
    TruckBrand truck_brand = TruckBrand::NONE;
};

#endif //COURSEWORK_REQUEST_H
