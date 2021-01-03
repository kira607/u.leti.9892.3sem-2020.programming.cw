#ifndef COURSEWORK_ROUTE_DB_H
#define COURSEWORK_ROUTE_DB_H

#define CSV_IO_NO_THREAD

#include <iomanip>
#include <fstream>

#include "../../../fast-cpp-csv-parser/csv.h"
#include "route_list.h"
#include "../../common/destination.h"
#include "../../common/input.h"

struct RouteDataBase
{
    RouteList list{};
    std::string db_path;

    explicit RouteDataBase(const std::string &db_path_ = "../dbs/routedb.csv");

    void PrintAll() const;
    void Print(int index) const;
    
    [[nodiscard]] Route *Find(Destination destination) const;

    void Edit(int index);
    void Add();
    void Delete(int index);

    void Exit();

    void _loadDataBase();
    void _updateDbFile() const;
};

#endif //COURSEWORK_ROUTE_DB_H
