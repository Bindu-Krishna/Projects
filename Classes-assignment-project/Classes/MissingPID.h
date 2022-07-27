#pragma once
#include "Common.h"

using namespace std;
typedef int ProcessID;


class PIDInfo {
public:
    PIDInfo()
    {
        ResetPIDInfo();
    }

    PIDInfo(ProcessID p_pid,
            bool p_system_flag,
            bool p_valid_path_flag)
    {
        m_pid = p_pid;
        if (p_system_flag)
            m_flags.set(static_cast<size_t>(ProcessExtraInfoFlags::SYSTEM_PROCESS));

        if(p_valid_path_flag)
            m_flags.set(static_cast<size_t>(ProcessExtraInfoFlags::HAS_VALID_IMAGE_PATH));
        
        cout << "system flag to set = " << p_system_flag << endl;
        cout << "valid flag to set = " << p_valid_path_flag << endl;
    }

    ~PIDInfo()
    {
        cout << ("Calling destructor") << endl;
        ResetPIDInfo();
    }

    void SetPIDInfo(ProcessID p_pid,
                    bool const & p_system_flag,
                    bool const & p_valid_path_flag)
    {
        m_pid = p_pid;
        if (p_system_flag)
            m_flags.set(static_cast<size_t>(ProcessExtraInfoFlags::SYSTEM_PROCESS));
        if (p_valid_path_flag)
            m_flags.set(static_cast<size_t>(ProcessExtraInfoFlags::HAS_VALID_IMAGE_PATH));
    }

    ProcessID GetPID()
    {
        return m_pid;
    }

    bool isInvalidPathFlagSet()
    {
        return !m_flags.test(static_cast<size_t>(ProcessExtraInfoFlags::HAS_VALID_IMAGE_PATH));
    }

    bool isSystemProcessFlagSet()
    {
        return m_flags.test(static_cast<size_t>(ProcessExtraInfoFlags::SYSTEM_PROCESS));
    }

    /* PIDInfo& operator=(const PIDInfo& t)
    {
    return *this;
    }*/

    void ResetPIDInfo()
    {
        m_pid = -1;
        m_flags.reset();
    }

private:
    ProcessID m_pid;
    std::bitset<static_cast<size_t>(ProcessExtraInfoFlags::BITSET_SIZE)> m_flags;
};

class MissingPIDs {

public:
    MissingPIDs()
    {
        ResetMissingPIDs();
    }

    std::map<ProcessID, unique_ptr<PIDInfo>>& GetMissingPID()
    {
        return m_missing_pid_info;
    }

    void SetMissingPID(ProcessID p_pid, bool p_system_flag,
                       bool p_valid_path_flag)
    {
        std::unique_ptr<PIDInfo> l_pid_info = std::make_unique<PIDInfo>(p_pid, p_system_flag, p_valid_path_flag);
        m_missing_pid_info[p_pid] = std::move(l_pid_info);
    }

    void ClearPID(ProcessID p_pid)
    {
        if (m_missing_pid_info.find(p_pid) != m_missing_pid_info.end())
        {
            m_missing_pid_info.erase(p_pid);
        }
    }

    void ResetMissingPIDs()
    {
        m_missing_pid_info.clear();
    }

private:
    map<ProcessID, unique_ptr<PIDInfo>> m_missing_pid_info;
};