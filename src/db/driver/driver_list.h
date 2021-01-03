#ifndef COURSEWORK_DRIVER_LIST_H
#define COURSEWORK_DRIVER_LIST_H

#include <iostream>
#include <sstream>

#include "driver.h"

struct DriverList
{
    Driver *head;
    Driver *tail;
    int size;

    [[nodiscard]] Driver *Get(int index) const;
    Driver *Add(const Driver &driver);
    void Delete(int index);
    void Free();

    void _check_index(const int &index) const;
};

#endif //COURSEWORK_DRIVER_LIST_H
