#include "request_handler.h"

RequestHandler::RequestHandler(const std::string &request_file_path, DataBases *data_bases)
{
    dbs = data_bases;
    request_path = request_file_path;
}

int RequestHandler::Run()
{
    _loadRequest();

    std::time_t now_time = std::time(nullptr);
    Date now = Date(now_time);

    dbs->schedule_db.Update(&now);

    if (request.departure_date.time <= now.time)
    {
        std::cerr << "requested departure date is too late!\n";
        return 100;
    }

    Route *target_route = dbs->route_db.Find(request.destination);
    request.target_route = target_route;

    int full_delivery_time = target_route->target_time_in_transit * 2 + target_route->loading_time;
    Delivery delivery = Delivery(request.departure_date.time, full_delivery_time);
    request.arrival_date = Date(delivery.end);

    Truck *truck = dbs->truck_db.Find(&request);
    if (!truck)
    {
        std::cerr << "Could not find free trucks on this date\n";
        return 120;
    }
    std::cout << "truck id:" << truck->id << "\n";
    delivery.truck_id = truck->id;

    int *drivers_ids = dbs->driver_db.Find(&request);
    if (!drivers_ids)
    {
        std::cerr << "Could not find free drivers on this date\n";
        return 121;
    }

    std::cout << "drivers ids: ";
    for (int i = 0; i < request.target_route->drivers; ++i)
    {
        std::cout << drivers_ids[i] << ";";
    }
    std::cout << "\n";
    delivery.drivers = request.target_route->drivers;
    delivery.drivers_ids = drivers_ids;

    dbs->schedule_db.Add(&delivery);

    dbs->CloseAll();

    return 0;
}

void RequestHandler::_loadRequest()
{
    int destination_code;
    int truck_brand_code;
    std::string departure_date;

    io::CSVReader<4> in(request_path);
    in.read_header(io::ignore_extra_column, "destination", "departure_date", "cargo_weight", "truck_brand");
    while(in.read_row(destination_code, departure_date, request.cargo_weight, truck_brand_code))
    {
        request.destination = static_cast<Destination>(destination_code);
        request.truck_brand = static_cast<TruckBrand>(truck_brand_code);
        request.departure_date.SetFromString(departure_date);
    }
}

