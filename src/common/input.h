#ifndef COURSEWORK_INPUT_H
#define COURSEWORK_INPUT_H

#define _min_int std::numeric_limits<int>::min()
#define _max_int std::numeric_limits<int>::max()

#include <iostream>
#include "truck_brand.h"
#include "destination.h"

int InputInt(const std::string& message = "Input: ", int l = _min_int, int r = _max_int);
std::string InputStr(const std::string& message = "Input: ");
TruckBrand InputTB(const std::string& message = "Input: ");
Destination InputDest(const std::string& message = "Input: ");

#endif //COURSEWORK_INPUT_H
