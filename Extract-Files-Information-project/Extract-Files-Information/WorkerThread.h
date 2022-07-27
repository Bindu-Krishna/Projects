#pragma once
#include "Common.h"

using namespace std;

enum class WorkerThreadStatus 
{
    THREAD_ACTIVE = 0,
    THREAD_PASSIVE = 1
};

class WorkerThread 
{
public:
    WorkerThread() = delete;
    WorkerThread(ProcessingStatus (*func)()) : m_func(func)
    {
        ResetEvent();
        CreateThread();
    };

    ~WorkerThread()
    {
        resetConfiguration();
    }
    void resetConfiguration();
    bool GetEvent();
    void SetEvent();
    void ResetEvent();
    void CreateThread();
    WorkerThreadStatus GetStatus();
private:
    unique_ptr<thread> m_thr_ptr;
    mutex m_mtx_thr_event;
    bool m_event;
    WorkerThreadStatus m_status;
    ProcessingStatus (*m_func)();
    void WorkerThreadFunction();
};