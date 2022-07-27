#include "Common.h"

HANDLE g_input_sem;
HANDLE g_op_complete_sem;

void ValidateInput(std::vector<string> p_paths);

int main (int argc, char* argv[])
{
    g_input_sem = CreateSemaphore(
        NULL,
        0,
        argc,
        NULL);

    if (g_input_sem == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    g_op_complete_sem = CreateSemaphore(
        NULL,
        0,
        1,
        NULL);

    if (g_op_complete_sem == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }
    if (argc > 1)
    {
        std::vector<string> l_paths;
        for (int i = 1; i < argc; ++i)
        {
            cout << argv[i] << "\n";
            l_paths.push_back(argv[i]);
        }

        try
        {
            ValidateInput(l_paths);
            std::thread clientThread (client, l_paths);
            std::thread serverThread (server);

            clientThread.join();
            serverThread.join();
        }
        catch (const std::exception& e)
        {
            cout << "exception caught = " << e.what() << endl;
            cout << "Usage Project1.exe C:\\Users\\bindu.k\\Documents\\test\\* \n";
        }
    }
    else
    {
        cout << "Usage Project1.exe <folder-path>" << endl;
    }

    CloseHandle(g_op_complete_sem);
    CloseHandle(g_input_sem);
    return 0;
}

void ValidateInput(std::vector<string> p_paths)
{
    for (auto & str : p_paths)
    {
        auto l_len = str.length();
        if ('*' != str[l_len - 1] || '\\' != str[l_len - 2])
        {
            throw std::exception("Invalid input");
        }
    }
}