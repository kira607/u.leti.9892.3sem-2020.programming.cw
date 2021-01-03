#ifndef COURSEWORK_SCHEDULE_DB_H
#define COURSEWORK_SCHEDULE_DB_H

#define CSV_IO_NO_THREAD

#include <fstream>

#include "../../../fast-cpp-csv-parser/csv.h"
#include "schedule.h"
#include "../driver/driver.h"
#include "../truck/truck.h"
#include "../../common/request.h"
#include "../../common/date.h"

struct ScheduleDataBase
{
    Schedule list{};
    std::string db_path;

    explicit ScheduleDataBase(const std::string &db_path_ = "../dbs/scheduledb.csv");

    void PrintAll() const;
    void Print(int index) const;

    bool IsFree(Truck *truck, Request *request) const;
    bool IsFree(Driver *driver, Request *request) const;
    void Update(Date *current_date);
    void Add(Delivery *delivery);

    void Exit();

    void _loadDataBase();
    void _updateDbFile();
    static int *_parseDriversIdsStr(const std::string &drivers_ids_str, int &drivers_count);
    static bool _isIntersection(Delivery *delivery, Request *request);
};

#endif //COURSEWORK_SCHEDULE_DB_H
