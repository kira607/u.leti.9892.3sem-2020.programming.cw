#include "route_db.h"

RouteDataBase::RouteDataBase(const std::string &db_path_)
{
    db_path = db_path_;
    _loadDataBase();
}

void RouteDataBase::PrintAll() const
{
    std::cout << std::left
              << std::setw(4)   << "id "
              << std::setw(15)  << "destination "
              << std::setw(15)  << "distance "
              << std::setw(15)  << "loading_time "
              << std::setw(15)  << "drivers "
              << std::setw(15)  << "target_time_in_transit\n";
    for(int i = 0; i < list.size; ++i)
    {
        Print(i);
    }
}

void RouteDataBase::Print(int index) const
{
    list._check_index(index);
    auto p = list.Get(index);
    std::cout << std::left
              << std::setw(3)  << p->id << " "
              << std::setw(14) << str(p->destination) << " "
              << std::setw(14)  << p->distance << " "
              << std::setw(14)  << p->loading_time << " "
              << std::setw(14)  << p->drivers << " "
              << std::setw(15)  << p->target_time_in_transit << "\n";
}

Route *RouteDataBase::Find(Destination destination) const
{
    for(int i = 0; i < list.size; ++i)
    {
        Route *current_route = list.Get(i);
        if(current_route->destination == destination)
        {
            return current_route;
        }
    }
    return nullptr;
}

void RouteDataBase::Edit(int index)
{
    list._check_index(index);
    Route *target_element = list.Get(index);
    while(true)
    {
        std::cout << "------------------------\n";
        Print(index);
        std::cout << "------------------------\n";
        std::cout << "Choose filed:\n";
        std::cout << "1 destination" << "\n";
        std::cout << "2 distance" << "\n";
        std::cout << "3 loading_time" << "\n";
        std::cout << "4 drivers" << "\n";
        std::cout << "5 time in transit" << "\n";
        std::cout << "0 Finish edit" << "\n";

        int option = InputInt("Input: ");

        switch (option)
        {
            case 1:
                target_element->destination = InputDest("New value: ");
                break;
            case 2:
                target_element->distance = InputInt("New value: ");
                break;
            case 3:
                target_element->loading_time = InputInt("New value: ");
                break;
            case 4:
                target_element->drivers = InputInt("New value: ");
                break;
            case 5:
                target_element->target_time_in_transit = InputInt("New value: ");
                break;
            case 0: _updateDbFile(); return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void RouteDataBase::Add()
{
    Route new_element;
    new_element.id = list.Get(list.size-1)->id + 1;
    new_element.destination = InputDest("destination: ");
    new_element.distance = InputInt("distance: ");
    new_element.loading_time = InputInt("loading_time: ");
    new_element.drivers = InputInt("drivers: ");
    new_element.target_time_in_transit = InputInt("time in transit: ");
    list.Add(new_element);
    _updateDbFile();
}

void RouteDataBase::Delete(int index)
{
    list.Delete(index);
    for(int i = index; i < list.size; ++i)
    {
        list.Get(i)->id = i;
    }
    _updateDbFile();
}

void RouteDataBase::Exit()
{
    list.Free();
}

void RouteDataBase::_loadDataBase()
{
    Route route{};

    io::CSVReader<6> in(db_path);
    in.read_header(io::ignore_extra_column, "id", "destination_code", "distance", "loading_time", "drivers",
                   "time_in_transit");
    int destination_code;
    while (in.read_row(route.id, destination_code, route.distance, route.loading_time, route.drivers,
                       route.target_time_in_transit))
    {
        route.destination = static_cast<Destination>(destination_code);
        list.Add(route);
    }
}

void RouteDataBase::_updateDbFile() const
{
    std::ofstream fout(db_path, std::ios_base::trunc);
    fout << "id,destination_code,distance,loading_time,drivers,time_in_transit\n";

    Route *p = list.head;
    while(p)
    {
        fout << p->id << ","
             << static_cast<int>(p->destination) << ","
             << p->distance << ","
             << p->loading_time << ","
             << p->drivers << ","
             << p->target_time_in_transit;
        fout << "\n";
        p = p->next;
    }
}