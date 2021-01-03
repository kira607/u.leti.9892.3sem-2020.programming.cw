#include "route_list.h"

Route *RouteList::Get(int index) const
{
    _check_index(index);

    auto p = head;
    for(int i = 0; i < index; ++i)
    {
        if(p->next)
            p = p->next;
        else
            return nullptr;
    }
    return p;
}

Route *RouteList::Add(const Route &route)
{
    auto *new_node = new Route(route);

    if (size == 0)
    {
        head = new_node;
        tail = new_node;
        new_node->prev = nullptr;
        new_node->next = nullptr;
    }
    else
    {
        new_node->prev = tail;
        new_node->prev->next = new_node;
        new_node->next = nullptr;
        tail = new_node;
    }

    ++size;
    return new_node;
}

void RouteList::Delete(int index)
{
    _check_index(index);

    if(size == 1 && index == 0)
    {
        Free();
        return;
    }

    if(index == 0)
    {
        Route *new_head = head->next;
        delete head;
        head = new_head;
        head->prev = nullptr;
        --size;
        return;
    }

    if(index == size - 1)
    {
        Route *new_tail = tail->prev;
        delete tail;
        tail = new_tail;
        tail->next = nullptr;
        --size;
        return;
    }

    auto p = Get(index);

    if (!p)
    {
        return;
    }

    p->next->prev = p->prev;
    p->prev->next = p->next;
    delete p;
    --size;
}

void RouteList::Free()
{
    Route *p = head;
    while(p != nullptr)
    {
        Route *next = p->next;
        delete p;
        p = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void RouteList::_check_index(const int &index) const
{
    if (index < 0 || index >= size)
    {
        std::stringstream message;
        message << "Index out of range (possible [0-" << size-1 << "], given " << index << ")";
        throw std::out_of_range(message.str().c_str());
    }
}