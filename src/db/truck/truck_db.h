#ifndef COURSEWORK_TRUCK_DB_H
#define COURSEWORK_TRUCK_DB_H

#define CSV_IO_NO_THREAD

#include <iomanip>
#include <fstream>

#include "../../../fast-cpp-csv-parser/csv.h"
#include "truck_list.h"
#include "../../common/request.h"
#include "../schedule/schedule_db.h"
#include "../../common/input.h"

struct TruckDataBase
{
    TruckList list{};
    std::string db_path{};
    ScheduleDataBase *schedule{};

    TruckDataBase() = default;
    explicit TruckDataBase(ScheduleDataBase *schedule_p, const std::string &db_path_ = "../dbs/truckdb.csv");

    void PrintAll() const;
    void Print(int index) const;
    
    [[nodiscard]] Truck *Find(Request *request) const;

    void Edit(int index);
    void Add();
    void Delete(int index);

    void Exit();

    void _loadDataBase();
    void _updateDbFile() const;
};

#endif //COURSEWORK_TRUCK_DB_H
