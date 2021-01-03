#include "delivery.h"

Delivery::Delivery()
{
    _init();
}

Delivery::Delivery(std::time_t start_time, int hours)
{
    _init();
    start = start_time;
    end = start + hours * 60 * 60;
}

void Delivery::_init()
{
    start = 0;
    end = 0;
    drivers_ids = nullptr;
    drivers = 0;
    truck_id = -1; 
    next = nullptr;
    prev = nullptr;
}