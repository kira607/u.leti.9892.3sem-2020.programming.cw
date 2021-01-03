#include "input.h"

int InputInt(const std::string& message, int l, int r)
{
    int element;
    bool input = true;
    while (input)
    {
        std::cout << message;
        std::cin >> element;
        if (std::cin.fail() || (element < l || element > r))
            std::cout << "Wrong input!\n";
        else
            input = false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return element;
}

std::string InputStr(const std::string &message)
{
    std::string element;
    bool input = true;
    while (input)
    {
        std::cout << message;
        std::cin >> element;
        if (std::cin.fail())
            std::cout << "Wrong input!\n";
        else
            input = false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return element;
}

TruckBrand InputTB(const std::string &message)
{
    std::cout << "1  Volvo\n";
    std::cout << "2  MercedesBenz\n";
    std::cout << "3  Man\n";
    std::cout << "4  Daf\n";
    std::cout << "5  Scania\n";
    std::cout << "6  Iveco\n";
    std::cout << "7  Renault\n";
    std::cout << "8  Nissan\n";
    std::cout << "9  Tatra\n";
    std::cout << "10 Mitsubishi\n";
    int code = InputInt(message, 1, 10);
    return static_cast<TruckBrand>(code);
}

Destination InputDest(const std::string &message)
{
    std::cout << "1 Omsk\n";
    std::cout << "2 Kaliningrad\n";
    std::cout << "3 StPetersburg\n";
    std::cout << "4 Novgorod\n";
    std::cout << "5 Sochi\n";
    std::cout << "6 Murmansk\n";
    int code = InputInt(message, 1, 6);
    return static_cast<Destination>(code);
}
