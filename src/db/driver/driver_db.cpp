#include "driver_db.h"

DriverDataBase::DriverDataBase(ScheduleDataBase *schedule_p, const std::string &db_path_)
{
    schedule = schedule_p;
    db_path = db_path_;
    _loadDataBase();
}

void DriverDataBase::PrintAll() const
{
    std::cout << std::left
              << std::setw(5)  << "id"
              << std::setw(11) << "surname"
              << std::setw(11) << "name"
              << std::setw(16) << "patronymic"
              << std::setw(12) << "truck_brand\n";

    for (int i = 0; i < list.size; ++i)
    {
        Print(i);
    }
}

void DriverDataBase::Print(int index) const
{
    list._check_index(index);
    auto p = list.Get(index);
    std::cout << std::left
              << std::setw(4)  << p->id << " "
              << std::setw(10) << p->surname << " "
              << std::setw(10) << p->name << " "
              << std::setw(15) << p->patronymic << " "
              << std::setw(13) << str(p->truck_brand) << "\n";
}

int *DriverDataBase::Find(Request *request) const
{
    Driver *pDriver = list.head;
    int *drivers_ids = new int[request->target_route->drivers];
    int found_free_drivers = 0;
    while(pDriver)
    {
        if((request->truck_brand != pDriver->truck_brand) ||
           (!schedule->IsFree(pDriver, request))
        )
        {
            pDriver = pDriver->next;
            continue;
        }
        drivers_ids[found_free_drivers] = pDriver->id;
        ++found_free_drivers;
        if(found_free_drivers < request->target_route->drivers)
        {
            pDriver = pDriver->next;
            continue;
        }
        return drivers_ids;
    }
    return nullptr;
}

void DriverDataBase::Edit(int index)
{
    list._check_index(index);
    Driver *target_element = list.Get(index);
    while(true)
    {
        std::cout << "------------------------\n";
        Print(index);
        std::cout << "------------------------\n";
        std::cout << "Choose filed:\n";
        std::cout << "1 surname" << "\n";
        std::cout << "2 name" << "\n";
        std::cout << "3 patronymic" << "\n";
        std::cout << "4 truck brand" << "\n";
        std::cout << "0 Finish edit" << "\n";

        int option = InputInt("Input: ");

        switch (option)
        {
            case 1:
                target_element->surname = InputStr("New value: ");
                break;
            case 2:
                target_element->name = InputStr("New value: ");
                break;
            case 3:
                target_element->patronymic = InputStr("New value: ");
                break;
            case 4:
                target_element->truck_brand = InputTB("New value: ");
                break;
            case 0: _updateDbFile(); return;
            default: std::cout << "\nIncorrect input\n\n";
        }
    }
}

void DriverDataBase::Add()
{
    Driver new_element;
    new_element.id = list.Get(list.size-1)->id + 1;
    new_element.surname = InputStr("surname: ");
    new_element.name = InputStr("name: ");
    new_element.patronymic = InputStr("patronymic: ");
    new_element.truck_brand = InputTB("truck brand: ");
    list.Add(new_element);
    _updateDbFile();
}

void DriverDataBase::Delete(int index)
{
    list.Delete(index);
    for(int i = index; i < list.size; ++i)
    {
        list.Get(i)->id = i;
    }
    _updateDbFile();
}

void DriverDataBase::Exit()
{
    list.Free();
}

void DriverDataBase::_loadDataBase()
{
    Driver driver{};

    io::CSVReader<5> in(db_path);
    in.read_header(io::ignore_extra_column, "id", "name", "surname", "patronymic", "brand_code");
    int brand_code;
    while(in.read_row(driver.id, driver.name, driver.surname, driver.patronymic, brand_code))
    {
        driver.truck_brand = static_cast<TruckBrand>(brand_code);
        list.Add(driver);
    }
}

void DriverDataBase::_updateDbFile() const
{
    std::ofstream fout(db_path, std::ios_base::trunc);
    fout << "id,name,surname,patronymic,brand_code\n";

    Driver *p = list.head;
    while(p)
    {
        fout << p->id << ","
             << p->name << ","
             << p->surname << ","
             << p->patronymic << ","
             << static_cast<int>(p->truck_brand);
        fout << "\n";
        p = p->next;
    }
}
