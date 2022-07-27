#pragma once
#include <memory>
#include <iostream>
#include <list>
#include <EventPublisher.h>

#define MAX_OFFLINE_EVENTS 250
class OfflineEvent {
public:
    OfflineEvent();
     ~OfflineEvent()
    {
    };
     void AddDataToList(std::unique_ptr<Event*> p_data_ptr);
     void DeleteDataFromList(std::unique_ptr<Event*> p_data_ptr);
     std::unique_ptr<Event*> GetDataFromList();
     void PublishOfflineEvents();
    std::list<std::unique_ptr<Event*>> m_events;
};

// being initialised from global initialiser
OfflineEvent g_offline_event;

bool GetOfflineEvents()
{
    
    while (true)
    {
        //Get Data from offline events list
        if (!g_offline_event.m_events.empty())
        {
            if (g_offline_event.m_events.size() >= MAX_OFFLINE_EVENTS)
            {
                // delete oldest event
                // delete file having oldest events
                
            }
            // save latest event into the file
            if (is_server_reachable)
            {
                while (no_more_files_left)
                {
                    ReadEventsfromFile();
                    PublishEventsToServer();
                }
            }
        }

        if (is_thread_exit_event)
        {
            break;
        }
    }
}