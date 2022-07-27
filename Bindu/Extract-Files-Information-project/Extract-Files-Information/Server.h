#pragma once
#include <list>

namespace Server
{
    ProcessingStatus FileReadThread();
    class FileListHandler 
    {
    public:
        FileListHandler();
        string GetData();
        void SetData(string);
        int GetSize();
        bool GetStatus();

    private:
        list<string> m_file_list;
        mutex m_mtx;
        bool m_is_active;
    };
}