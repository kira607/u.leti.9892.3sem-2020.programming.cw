#ifndef COURSEWORK_SCHEDULE_H
#define COURSEWORK_SCHEDULE_H

#include <iostream>
#include <sstream>

#include "delivery.h"

struct Schedule
{
    Delivery *head;
    Delivery *tail;
    int size;

    [[nodiscard]] Delivery *Get(int index) const;
    Delivery *Add(const Delivery &delivery);
    void Delete(int index);
    void Free();

    void _check_index(const int &index) const;
};

#endif //COURSEWORK_SCHEDULE_H
