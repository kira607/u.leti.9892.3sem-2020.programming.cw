#include "schedule_db.h"

ScheduleDataBase::ScheduleDataBase(const std::string &db_path_)
{
    db_path = db_path_;
    _loadDataBase();
}

void ScheduleDataBase::PrintAll() const
{
    for(int i = 0; i < list.size; ++i)
    {
        Print(i);
    }
}

void ScheduleDataBase::Print(int index) const
{
    list._check_index(index);
    auto p = list.Get(index);
    std::cout << p->start << " "
              << p->end << " "
              << p->truck_id << " ";
    for(int i = 0; i < p->drivers; ++i)
    {
        std::cout << p->drivers_ids[i] << ";";
    }
    std::cout << "\n";
}

bool ScheduleDataBase::IsFree(Truck *truck, Request *request) const
{
    Delivery *pDelivery = list.head;
    while(pDelivery)
    {
        if(pDelivery->truck_id == truck->id)
        {
            if(_isIntersection(pDelivery, request))
            {
                return false;
            }
        }
        pDelivery = pDelivery->next;
    }
    return true;
}
    
bool ScheduleDataBase::IsFree(Driver *driver, Request *request) const
{
    Delivery *pDelivery = list.head;
    while(pDelivery)
    {
        for(int i = 0; i < pDelivery->drivers; ++i)
        {
            if(pDelivery->drivers_ids[i] == driver->id)
            {
                if(_isIntersection(pDelivery, request))
                {
                    return false;
                }
            }
        }
        pDelivery = pDelivery->next;
    }
    return true;
}

void ScheduleDataBase::Update(Date *date)
{
    Delivery *pDelivery = list.head;
    int index = 0;
    while(pDelivery)
    {
        Delivery *next = pDelivery->next;
        if(pDelivery->end < date->time) // if delivery has ended
            list.Delete(index);
        else
            ++index;
        pDelivery = next;
    }
    _updateDbFile();
}

void ScheduleDataBase::Add(Delivery *delivery)
{
    list.Add(*delivery);
    _updateDbFile();
}

void ScheduleDataBase::Exit()
{
    list.Free();
}

void ScheduleDataBase::_loadDataBase()
{
    Delivery delivery{};
    std::string drivers_ids_str;

    io::CSVReader<4> in(db_path);
    in.read_header(io::ignore_extra_column, "start", "end", "truck_id", "drivers_ids");
    while(in.read_row(delivery.start, delivery.end, delivery.truck_id, drivers_ids_str))
    {
        delivery.drivers_ids = _parseDriversIdsStr(drivers_ids_str, delivery.drivers);
        list.Add(delivery);
    }
}

void ScheduleDataBase::_updateDbFile()
{
    std::ofstream fout(db_path, std::ios_base::trunc);
    fout << "start,end,truck_id,drivers_ids\n";

    Delivery *pDelivery = list.head;
    while(pDelivery)
    {
        fout << pDelivery->start << ","
             << pDelivery->end << ","
             << pDelivery->truck_id << ",";
        for(int i = 0; i < pDelivery->drivers; ++i)
        {
            fout << pDelivery->drivers_ids[i] << " ";
        }
        fout << "\n";
        pDelivery = pDelivery->next;
    }
}

int *ScheduleDataBase::_parseDriversIdsStr(const std::string &drivers_ids_str, int &drivers_count)
{
    drivers_count = 0;
    int *drivers_ids = new int[1];
    std::stringstream ss{drivers_ids_str};
    int read_element;
    while(ss >> read_element)
    {
        drivers_ids[drivers_count] = read_element;
        ++drivers_count;
        drivers_ids = (int*)realloc(drivers_ids, sizeof(int) * (drivers_count + 1));
    }
    return drivers_ids;
}

bool ScheduleDataBase::_isIntersection(Delivery *delivery, Request *request)
{
    int a1 = request->departure_date.time;
    int a2 = request->arrival_date.time;
    int b1 = delivery->start;
    int b2 = delivery->end;

    if(a1 < b1 && a2 < b1)
        return false;
    if(a1 > b2 && a2 > b2)
        return false;
    return true;
}