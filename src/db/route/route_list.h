#ifndef COURSEWORK_ROUTE_LIST_H
#define COURSEWORK_ROUTE_LIST_H

#include <iostream>
#include <sstream>

#include "route.h"

struct RouteList
{
    Route *head;
    Route *tail;
    int size;

    [[nodiscard]] Route *Get(int index) const;
    Route *Add(const Route &route);
    void Delete(int index);
    void Free();

    void _check_index(const int &index) const;
};

#endif //COURSEWORK_ROUTE_LIST_H
