#include "truck_db.h"

TruckDataBase::TruckDataBase(ScheduleDataBase *schedule_p, const std::string &db_path_)
{
    schedule = schedule_p;
    db_path = db_path_;
    _loadDataBase();
}

void TruckDataBase::PrintAll() const
{
    std::cout << std::left
              << std::setw(4)  << "id "
              << std::setw(14) << "brand "
              << std::setw(10)  << "capacity "
              << std::setw(5)  << "transportation_distance\n";
    for(int i = 0; i < list.size; ++i)
    {
        Print(i);
    }
}

void TruckDataBase::Print(int index) const
{
    list._check_index(index);
    auto p = list.Get(index);
    std::cout << std::left
              << std::setw(3)  << p-> id << " "
              << std::setw(13) << str(p->brand) << " "
              << std::setw(9)  << p->capacity << " "
              << std::setw(5)  << p->transportation_distance << "\n";
}

Truck *TruckDataBase::Find(Request *request) const
{
    Truck *pTruck = list.head;
    while(pTruck)
    {
        if(
            (pTruck->brand != request->truck_brand) ||
            (pTruck->capacity < request->cargo_weight) || 
            (pTruck->transportation_distance < request->target_route->distance) ||
            (!schedule->IsFree(pTruck, request))
        )
        {
            pTruck = pTruck->next;
            continue;
        }
        return pTruck;
    }
    return nullptr;
}

void TruckDataBase::Edit(int index)
{
    list._check_index(index);
    Truck *target_element = list.Get(index);
    while(true)
    {
        std::cout << "------------------------\n";
        Print(index);
        std::cout << "------------------------\n";
        std::cout << "Choose filed:\n";
        std::cout << "1 brand" << "\n";
        std::cout << "2 capacity" << "\n";
        std::cout << "3 distance" << "\n";
        std::cout << "0 Finish edit" << "\n";

        int option = InputInt("Input: ");

        switch (option)
        {
            case 1:
                target_element->brand = InputTB("New value: ");
                break;
            case 2:
                target_element->capacity = InputInt("New value: ");
                break;
            case 3:
                target_element->transportation_distance = InputInt("New value: ");
                break;
            case 0: _updateDbFile(); return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void TruckDataBase::Add()
{
    Truck new_element;
    new_element.id = list.Get(list.size-1)->id + 1;
    new_element.brand = InputTB("brand: ");
    new_element.capacity = InputInt("capacity: ");
    new_element.transportation_distance = InputInt("transportation distance: ");
    list.Add(new_element);
    _updateDbFile();
}

void TruckDataBase::Delete(int index)
{
    list.Delete(index);
    for(int i = index; i < list.size; ++i)
    {
        list.Get(i)->id = i;
    }
    _updateDbFile();
}

void TruckDataBase::Exit()
{
    list.Free();
}

void TruckDataBase::_loadDataBase()
{
    Truck truck{};

    io::CSVReader<4> in(db_path);
    in.read_header(io::ignore_extra_column, "id", "brand", "capacity", "transportation_distance");
    int brand_code;
    while(in.read_row(truck.id, brand_code, truck.capacity, truck.transportation_distance))
    {
        truck.brand = static_cast<TruckBrand>(brand_code);
        list.Add(truck);
    }
}

void TruckDataBase::_updateDbFile() const
{
    std::ofstream fout(db_path, std::ios_base::trunc);
    fout << "id,brand,capacity,transportation_distance\n";

    Truck *p = list.head;
    while(p)
    {
        fout << p->id << ","
             << static_cast<int>(p->brand) << ","
             << p->capacity << ","
             << p->transportation_distance;
        fout << "\n";
        p = p->next;
    }
}


