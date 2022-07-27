#pragma once
#include <memory>
#include <iostream>
#include <list>
/******************************************************************************************************/
/* This is the main thread for publishing all types of events to the Backend server                  */
/* Types of events include File events , process events, network events, watchdog events and the like*/

#define MAX_NUM_EVENTS 100

enum class EventType 
{
    FILE_EVENT = 0,
    PROCESS_EVENT,
    NETWORK_EVENT,
    WATCHDOG_EVENT,
    SYSTEM_EVENT,
    INVALID
};

enum class EventCategory {
    BASE_CATEGORY = 0, // to be filled
    INVALID
};

class Event 
{
public:
    Event();
    virtual ~Event(){};
    //.....
private:
    EventType m_type;
    EventCategory m_category;
};

// Define FileEvent , ProcessEvent, NEtworkEvent keeping Event Class as the base

class Events 
{
public:
    Events()
    {
    }
    ~Events()
    {
    };
    void AddDataToList(std::unique_ptr<Event*> p_data_ptr);
    void DeleteDataFromList(std::unique_ptr<Event*> p_data_ptr);
    std::unique_ptr<Event*> GetDataFromList();
    void PublishEvents();

private:
    std::list<std::unique_ptr<Event*>> m_events;
    //.... other members as needed
};

// parallel queues 
// map<PRIORITY, std::list<std::unique_ptr<Event*>>> m_priority_based_...
// COMMAND PATTERN / VISITOR
// PUB - SUB
// thre
void Events::PublishEvents()
{
    while (true)
    {
        void * l_buffer = nullptr;
        int l_buf_size = 0;
        while (!m_events.empty())
        {
            if (m_events.size() > MAX_NUM_EVENTS)
            {
                // form a buffer with 20 events each (consider popping out events from list)
                // fill buffer size
               
            }
            else
            {
                // form buffer for every event (consider popping out events from list)
                
            }
            ServerResponse l_response;
            try
            {
                // SendData(l_buffer, "EVENTS_ROUTE", & l_response);
            }
            catch (std::exception const & e)
            {
                // log exception + take necessary action based on exception type
            }
            if (is_thread_exit_event)
            {
                break;
            }
        }
    }
}