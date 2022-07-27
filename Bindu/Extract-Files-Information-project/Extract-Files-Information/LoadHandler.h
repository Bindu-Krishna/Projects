#pragma once
#include "Common.h"
#include "WorkerThread.h"

#define FILE_LIST_THRESHOLD_LEVEL1  25
#define FILE_LIST_THRESHOLD_LEVEL2  50
#define FILE_LIST_THRESHOLD_LEVEL3  75
#define FILE_LIST_THRESHOLD_LEVEL4  100

#define NUM_THREAD_LEVEL0  0 // no input to process, delete all threads
#define NUM_THREAD_LEVEL1  1
#define NUM_THREAD_LEVEL2  2
#define NUM_THREAD_LEVEL3  3
#define NUM_THREAD_LEVEL4  4

class LoadHandler 
{
public:
    LoadHandler();
    ~LoadHandler()
    {
        resetConfiguration();
    };
    void ManageLoad(int p_num_files);
    void resetConfiguration();
    void HandleThreadsNumber(int p_current_num_threads, int p_required_num_threads);
    void PrintStats();

private:
    mutex m_mtx_thread_vector;
    vector<unique_ptr<WorkerThread>> m_thread_vector;
    void AddThreads(int p_num_threads_to_add);
    void DeleteThreads(int p_num_threads_to_delete);
    void CleanupUnusedThreads();
};