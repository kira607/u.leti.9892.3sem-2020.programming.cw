#ifndef COURSEWORK_DESTINATION_H
#define COURSEWORK_DESTINATION_H

#include <string>
#include <stdexcept>

enum class Destination
{
    Omsk = 1,
    Kaliningrad = 2,
    StPetersburg = 3,
    Novgorod = 4,
    Sochi = 5,
    Murmansk = 6,
    NONE = 0
};

std::string str(Destination destination);

#endif //COURSEWORK_DESTINATION_H
