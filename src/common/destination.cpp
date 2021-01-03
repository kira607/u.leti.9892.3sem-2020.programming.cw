#include "destination.h"

std::string str(Destination destination)
{
    switch(destination)
    {
        case Destination::Omsk: return "Omsk";
        case Destination::Kaliningrad: return "Kaliningrad";
        case Destination::StPetersburg: return "StPetersburg";
        case Destination::Novgorod: return "Novgorod";
        case Destination::Sochi: return "Sochi";
        case Destination::Murmansk: return "Murmansk";
        case Destination::NONE: return "NONE";
    }
    throw std::out_of_range("Unexpected destination value");
}