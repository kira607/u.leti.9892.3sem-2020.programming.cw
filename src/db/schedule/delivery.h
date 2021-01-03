#ifndef COURSEWORK_DELIVERY_H
#define COURSEWORK_DELIVERY_H

#include <ctime>

struct Delivery
{
    std::time_t start{};
    std::time_t end{};
    int *drivers_ids{};
    int drivers{};
    int truck_id{};

    Delivery *next{};
    Delivery *prev{};

    Delivery();
    Delivery(std::time_t start_time, int hours);
    void _init();
};

#endif //COURSEWORK_DELIVERY_H
