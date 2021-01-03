#ifndef COURSEWORK_REQUEST_HANDLER_H
#define COURSEWORK_REQUEST_HANDLER_H

#define CSV_IO_NO_THREAD

#include "../../fast-cpp-csv-parser/csv.h"
#include "../common/request.h"
#include "../common/dbs.h"

struct RequestHandler
{
    Request request;
    std::string request_path;
    DataBases *dbs;

    RequestHandler(const std::string &request_file_path, DataBases *data_bases);
    int Run();

    void _loadRequest();
};

#endif //COURSEWORK_REQUEST_HANDLER_H
