#include "WorkerThread.h"

void WorkerThread::resetConfiguration()
{
    if (m_thr_ptr != nullptr )
    {
        SetEvent();
        m_thr_ptr->join();
        m_thr_ptr = nullptr;
    }
    ResetEvent();
}

bool WorkerThread::GetEvent()
{
    const lock_guard<mutex> lock(m_mtx_thr_event);
    return m_event;
}

void WorkerThread::SetEvent()
{
    const lock_guard<mutex> lock(m_mtx_thr_event);
    m_event = true;
}

void WorkerThread::ResetEvent()
{
    const lock_guard<mutex> lock(m_mtx_thr_event);
    m_event = false;
}

WorkerThreadStatus WorkerThread::GetStatus()
{
    return m_status;
}

void WorkerThread::WorkerThreadFunction()
{
    while (true)
    {
        if (GetEvent() == true)
        {
            break;
        }
        else
        {
            try
            {
                ProcessingStatus l_status = m_func();
                if (ProcessingStatus::NO_INPUT == l_status)
                {
                    m_status = WorkerThreadStatus::THREAD_PASSIVE;
                }
            }
            catch (const std::exception& e)
            {
                cout << "exception caught = " << e.what() << "getlast error = " << GetLastError() << endl;
                //continue with thread processing until notified
            }
        }
    }
    return;
}

void WorkerThread::CreateThread()
{
    thread thr(&WorkerThread::WorkerThreadFunction, this);
    m_status = WorkerThreadStatus::THREAD_ACTIVE;
    m_thr_ptr = make_unique<thread>(move(thr));
    return;
}