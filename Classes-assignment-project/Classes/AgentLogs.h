#pragma once

#include "MissingPID.h"

class AgentLogsHandler {
public:
    AgentLogsHandler()
    {
        m_missing_pid_info.ResetMissingPIDs();
    }

    void GetMissingPIDsDump()
    {
        for (auto iter = m_missing_pid_info.GetMissingPID().begin(); iter != m_missing_pid_info.GetMissingPID().end(); iter++)
        {
            iter->first;
            cout << "pid = " << iter->second->GetPID() << endl;
            cout << "system flag = " << iter->second->isSystemProcessFlagSet() << endl;
            cout << "invalid path = " << iter->second->isInvalidPathFlagSet() << endl;
        }
    }

    MissingPIDs& GetMissingPIDs()
    {
        return m_missing_pid_info;
    }

    void ClearMissingPIDs()
    {
        m_missing_pid_info.ResetMissingPIDs();
    }

private:
    MissingPIDs m_missing_pid_info;
}; 