#include "Common.h"

vector<string> g_input_list;
BOOL g_is_input_list_full = FALSE;
mutex g_input_list_mutex;

void client(std::vector<string> p_paths)
{
    for (auto & l_path : p_paths)
    {
        g_input_list.push_back(l_path);
        if (ReleaseSemaphore(
            g_input_sem,
            1,
            NULL) == 0)
        {
            printf("ReleaseSemaphore error: %d\n", GetLastError());
        }
    }

    g_input_list_mutex.lock();
    g_is_input_list_full = TRUE;
    g_input_list_mutex.unlock();

    DWORD dwWaitResult = WaitForSingleObject(
        g_op_complete_sem,
        INFINITE);

    switch (dwWaitResult)
    {
        case WAIT_OBJECT_0:
            return;
        case WAIT_TIMEOUT:
            cout << "Thread %d: wait timed out\n" << GetCurrentThreadId();
            break;
        default:
            cout << "Default case for client thread \n";
            break;
    }
    return;
}

