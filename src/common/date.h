#ifndef COURSEWORK_DATE_H
#define COURSEWORK_DATE_H

#include <string>
#include <ctime>

struct Date
{
    std::string default_format{};
    std::tm *date{};
    std::time_t time{};

    Date();
    explicit Date(std::time_t time_to_set);
    explicit Date(const std::string &date_str, const std::string &format = "");
    void SetFromString(const std::string &date_str, const std::string &format = "");
    void SetFromTime(time_t time_to_set);
    [[nodiscard]] std::string String() const;

    void _init();
};

#endif //COURSEWORK_DATE_H
