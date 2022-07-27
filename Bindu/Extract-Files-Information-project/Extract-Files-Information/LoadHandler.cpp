#include "LoadHandler.h"
#include "Server.h"

LoadHandler::LoadHandler()
{
    m_thread_vector.clear();
}

void LoadHandler::resetConfiguration()
{
    for (auto & thread_ptr : m_thread_vector)
    {
        thread_ptr->resetConfiguration();
    }
    m_thread_vector.clear();
}


void LoadHandler::ManageLoad(int p_num_files)
{
    size_t l_file_vector_size = p_num_files;
 
    m_mtx_thread_vector.lock();
    size_t l_thread_vector_size = m_thread_vector.size();
    m_mtx_thread_vector.unlock();

    if (l_file_vector_size == 0)
    {
        HandleThreadsNumber(l_thread_vector_size, NUM_THREAD_LEVEL0);
    }
    else if (l_file_vector_size <= FILE_LIST_THRESHOLD_LEVEL1)
    {
        HandleThreadsNumber(l_thread_vector_size, NUM_THREAD_LEVEL1);
    }
    else if (l_file_vector_size <= FILE_LIST_THRESHOLD_LEVEL2)
    {
        HandleThreadsNumber(l_thread_vector_size, NUM_THREAD_LEVEL2);
    }
    else if (l_file_vector_size <= FILE_LIST_THRESHOLD_LEVEL3)
    {
        HandleThreadsNumber(l_thread_vector_size, NUM_THREAD_LEVEL3);
    }
    else
    {
        HandleThreadsNumber(l_thread_vector_size, NUM_THREAD_LEVEL4);
    }

    CleanupUnusedThreads();
    // Enable this to check on active number of threads at the moment
    //PrintStats();
    return;
}

void LoadHandler::HandleThreadsNumber(int p_current_num_threads, int p_required_num_threads)
{
    try
    {
        if (p_current_num_threads < p_required_num_threads)
        {
            AddThreads(p_required_num_threads - p_current_num_threads);
        }
        else if (p_current_num_threads > p_required_num_threads)
        {
            DeleteThreads(p_current_num_threads - p_required_num_threads);
        }
        else
        {
            cout << "Correct number of threads present: Nothing to do" << endl;
        }
    }
    catch (const std::exception& e)
    {
        cout << "exception caught = " << e.what() << "getlast error = " << GetLastError() << endl;
    }
}

void LoadHandler::AddThreads(int p_count)
{
    for (int iter = 0; iter < p_count; iter++)
    {
        unique_ptr<WorkerThread> l_ptr = make_unique<WorkerThread>(Server::FileReadThread);
        const lock_guard<mutex> lock(m_mtx_thread_vector);
        m_thread_vector.push_back(move(l_ptr));
    }
}

void LoadHandler::DeleteThreads(int p_count)
{
    for (int iter = 0; iter < p_count; iter++)
    {
        unique_ptr<WorkerThread> l_ptr = move(m_thread_vector.back());
        l_ptr->resetConfiguration();
        const lock_guard<mutex> lock(m_mtx_thread_vector);
        m_thread_vector.pop_back();
    }
}

void LoadHandler::CleanupUnusedThreads()
{
    int iter = 0;
    for (auto & l_thread : m_thread_vector)
    {
        if (l_thread->GetStatus() == WorkerThreadStatus::THREAD_PASSIVE)
        {
            l_thread->resetConfiguration();
            const lock_guard<mutex> lock(m_mtx_thread_vector);
            m_thread_vector.erase(m_thread_vector.begin() + iter);
        }
        iter++;
    }
}

void LoadHandler::PrintStats()
{
    const lock_guard<mutex> lock(m_mtx_thread_vector);
    cout << "*************************************************************\n";
    cout << "******* Number of threads in Use = " << m_thread_vector.size() << endl;
    cout << "*************************************************************\n";
}