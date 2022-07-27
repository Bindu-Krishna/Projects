#include "AgentLogs.h"

int main()
{
    unique_ptr<AgentLogsHandler> GAgentLogsHandler;
    GAgentLogsHandler = std::make_unique<AgentLogsHandler>();
    GAgentLogsHandler->GetMissingPIDs().SetMissingPID(123, true, true);
    GAgentLogsHandler->GetMissingPIDsDump();
    cout << "completed";
    return 0;
}