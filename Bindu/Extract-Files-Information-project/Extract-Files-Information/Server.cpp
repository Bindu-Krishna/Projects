#include <list>
#include <stdexcept>
#include <fstream>
#include "Common.h"
#include "Server.h"
#include "LoadHandler.h"

#define MAX_BYTES_TO_READ 2

Server::FileListHandler g_file_list_handler;

mutex g_mtx_no_more_files;
BOOL g_is_no_more_files = FALSE;

void HandleFileInfo(string &p_folder_path)
{
    //https://docs.microsoft.com/en-us/windows/win32/fileio/listing-the-files-in-a-directory
    vector<string> l_sub_folders = {p_folder_path};
    string l_ignore(".");

    while (!l_sub_folders.empty())
    {
        WIN32_FIND_DATA ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        string l_folder = l_sub_folders.back();
        l_sub_folders.pop_back();

        hFind = FindFirstFile(l_folder.c_str(), &ffd);
        if (INVALID_HANDLE_VALUE == hFind)
        {
            throw std::exception("FindFirstFile INVALID_HANDLE_VALUE");
        }

        do
        {
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (ffd.cFileName[0] != '.')
                {
                    string l_temp;
                    l_temp.assign(l_folder, 0, (l_folder.length() - 2));
                    string l_sub_folder = l_temp + "\\" + ffd.cFileName + "\\*";
                    l_sub_folders.push_back(l_sub_folder);
                }
            }
            else
            {
                string l_temp;
                l_temp.assign(l_folder, 0, (l_folder.length() - 2));
                string l_file_name = l_temp + "\\" + ffd.cFileName;
                g_file_list_handler.SetData(l_file_name);
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES)
        {
            throw std::exception("FindFirstFile Files still present for processing");
        }

        FindClose(hFind);
    }

    return;
}

void HandleInputInformation()
{
    while (true)
    {
        try
        {
            DWORD dwWaitResult = WaitForSingleObject(
                g_input_sem,   // handle to semaphore
                INFINITE);

            switch (dwWaitResult)
            {
                // The semaphore object was signaled.
                case WAIT_OBJECT_0:
                    break;

                case WAIT_TIMEOUT:
                    printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                    break;
                default :
                    break;
            }

            g_input_list_mutex.lock();
            BOOL l_is_list_full = g_is_input_list_full;
            g_input_list_mutex.unlock();

            if (!g_input_list.empty())
            {
                std::string l_path_info = (std::string)(g_input_list.back());
                g_input_list.pop_back();
                HandleFileInfo(l_path_info);
            }

            if (l_is_list_full == TRUE && g_input_list.empty())
            {
                const lock_guard<mutex> lock(g_mtx_no_more_files);
                g_is_no_more_files = TRUE;
                break;
            }
        }
        catch (const std::exception& e)
        {
            cout << "exception caught = " << e.what() << "getlast error = " << GetLastError() << endl;
        }
    }

    return;
}

void server()
{
    LoadHandler l_load;

    thread handle_input_info (HandleInputInformation);

    while (true)
    {
        if (g_file_list_handler.GetStatus())
        {
            int l_size = g_file_list_handler.GetSize();
            l_load.ManageLoad(l_size);
            Sleep(500);
            l_size = g_file_list_handler.GetSize();
            BOOL is_no_more_files = FALSE;
            {
                const lock_guard<mutex> lock(g_mtx_no_more_files);
                is_no_more_files = g_is_no_more_files;
            }
            if (l_size == 0 && is_no_more_files)
            {
                break;
            }
        }
        else
        {
            Sleep(500);
        }
    }

    handle_input_info.join();

    if (ReleaseSemaphore(
        g_op_complete_sem,
        1,
        NULL) == 0)
    {
        printf("ReleaseSemaphore error: %d\n", GetLastError());
    }
    return;
}

namespace Server
{
    FileListHandler::FileListHandler()
    {
        m_file_list.clear();
        m_is_active = false;
    }

    string FileListHandler::GetData()
    {
        const lock_guard<mutex> lock(m_mtx);
        string l_str = "";
        if (!m_file_list.empty())
        {
            l_str = m_file_list.front();
            m_file_list.pop_front();
        }
        return l_str;
    }

    void FileListHandler::SetData(string p_str)
    {
        const lock_guard<mutex> lock(m_mtx);
        m_file_list.push_back(p_str);
        m_is_active = true;
        return;
    }

    int FileListHandler::GetSize()
    {
        const lock_guard<mutex> lock(m_mtx);
        return m_file_list.size();
    }

    bool FileListHandler::GetStatus()
    {
        const lock_guard<mutex> lock(m_mtx);
        return m_is_active;
    }
    ProcessingStatus FileReadThread()
    {
        string l_file_path = g_file_list_handler.GetData();
        ProcessingStatus l_status = ProcessingStatus::SUCCESS;
        if (!l_file_path.empty())
        {
            ifstream l_file_stream;
            l_file_stream.open(l_file_path, ios::in | ios::binary);
            if (!l_file_stream.good())
            {
                string l_exception = "File stream not good : Path = " + l_file_path;
                throw std::exception(l_exception.c_str());
            }
            l_file_stream.seekg(0, ios::beg);

            char op_Data[MAX_BYTES_TO_READ + 1] = "";
            l_file_stream.read(op_Data, MAX_BYTES_TO_READ);
            l_file_stream.seekg(0, ios::end);
            int l_file_size = l_file_stream.tellg();
            l_file_stream.close();

            std::size_t l_file_name_pos = l_file_path.find_last_of("/\\");
            string l_file_name = l_file_path.substr(l_file_name_pos + 1);
            size_t l_extension_pos = l_file_name.find_last_of(".");
            string l_extension_type;
            if (l_extension_pos != string::npos)
                l_extension_type = l_file_name.substr(l_extension_pos + 1);
            else
                l_extension_type = l_file_name;

            cout << l_file_path << " " << l_file_size << " bytes " << l_extension_type << " " << op_Data << endl;
        }
        else
        {
            //cout << "No input to process : stop processing\n";
            l_status = ProcessingStatus::NO_INPUT;
        }

        return l_status;
    }
}

