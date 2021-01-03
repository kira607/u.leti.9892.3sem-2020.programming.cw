#include "date.h"

Date::Date()
{
    _init();
}

Date::Date(std::time_t time_to_set)
{
    _init();
    SetFromTime(time_to_set);
}

Date::Date(const std::string &date_str, const std::string &format)
{
    _init();
    SetFromString(date_str, format);
}

void Date::SetFromString(const std::string &date_str, const std::string &format)
{
    std::string local_format;
    if (format.empty())
        local_format = default_format;
    else
        local_format = format;

    strptime(date_str.c_str(), local_format.c_str(), date);
    time = std::mktime(date);
}

void Date::SetFromTime(std::time_t time_to_set)
{
    date = localtime(&time_to_set);
    time = mktime(date);
}

[[nodiscard]] std::string Date::String() const
{
    int buff_size = 20;
    char buffer[buff_size];
    strftime(buffer, buff_size, default_format.c_str(), date);
    return std::string(buffer);
}

void Date::_init()
{
    time = 0;
    date = new tm{};
    default_format = "%d.%m.%Y %H:%M";
}
