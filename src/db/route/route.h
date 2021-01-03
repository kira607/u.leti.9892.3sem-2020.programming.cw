#ifndef COURSEWORK_ROUTE_H
#define COURSEWORK_ROUTE_H

#include "../../common/destination.h"

struct Route
{
    Destination destination;
    int id;
    int distance;
    int loading_time;
    int drivers;
    int target_time_in_transit;

    Route *prev;
    Route *next;

    Route();
    Route(const Route &route);
};

#endif //COURSEWORK_ROUTE_H
