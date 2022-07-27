#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include "MyEventProvider.h"

using namespace std;
int main()
{
    const char* custom_log_name = "MyEventProvider";

    // create registry keys for ACLing described on MSDN: http://msdn2.microsoft.com/en-us/library/aa363648.aspx

    /*  Logging into event viewer = {"commandline":"IkM6XHRlbXBcaG9zdFxub3RlcGFkLmV4ZSIg","eventCategory":1,"eventGenerationStage":0,"eventPid":15076,"eventReason":0,"eventTime":1627024493,"eventType":1,"fingerprint":{"type":2,"value":"423d3ade2f14572c5bd5f546973eb493"},"fingerprintInfo":{"type":2,"value":"423d3ade2f14572c5bd5f546973eb493"},"operationStatus":0,"parentsInfo":[{"fingerprint":{"type":2,"value":"4bf8cf1a2379b0054860ec220ca329b9"},"fingerprintInfo":{"type":2,"value":"4bf8cf1a2379b0054860ec220ca329b9"},"networkConnectionsInfo":{"totalCount":0},"path":"C:\\WINDOWS\\EXPLORER.EXE","pid":8612,"ppid":-1,"trustInfo":{"positives":0,"score":100,"total":50},"username":"INCT-BINDUK\\bindu.k"}],"path":"C:\\TEMP\\HOST\\NOTEPAD.EXE","pid":15076,"policy":{"id":"60af6c339d9698f6496dae19","vid":"60fa618fd5a69d4f433ba058"},"ppid":8612,"ruleInfo":{"pathInfo":{"type":0,"value":"C:\\TEMP\\HOST\\NOTEPAD.EXE"},"ruleUUID":"60fa618fd5a69dfcfe3ba052"},"trustInfo":{"positives":0,"score":100,"total":50},"username":"INCT-BINDUK\\bindu.k"}*/
    HANDLE event_log = RegisterEventSource(NULL, custom_log_name);
    std::string temp = "Information Log";
    temp.assign("{ \"commandline\":\"IkM6XHRlbXBcaG9zdFxub3RlcGFkLmV4ZSIg\",\"eventCategory\" : 1,\"eventGenerationStage\" : 0,\"eventPid\" : 15076,\"eventReason\" : 0,\"eventTime\" : 1627024493,\"eventType\" : 1,\"fingerprint\" : {\"type\":2,\"value\" : \"423d3ade2f14572c5bd5f546973eb493\"},\"fingerprintInfo\" : {\"type\":2,\"value\" : \"423d3ade2f14572c5bd5f546973eb493\"},\"operationStatus\" : 0,\"parentsInfo\" : [{\"fingerprint\":{\"type\":2,\"value\" : \"4bf8cf1a2379b0054860ec220ca329b9\"},\"fingerprintInfo\" : {\"type\":2,\"value\" : \"4bf8cf1a2379b0054860ec220ca329b9\"},\"networkConnectionsInfo\" : {\"totalCount\":0},\"path\" : \"C:\\WINDOWS\\EXPLORER.EXE\",\"pid\" : 8612,\"ppid\" : -1,\"trustInfo\" : {\"positives\":0,\"score\" : 100,\"total\" : 50},\"username\" : \"INCT-BINDUK\\bindu.k\"}],\"path\" : \"C:\\TEMP\\HOST\\NOTEPAD.EXE\",\"pid\" : 15076,\"policy\" : {\"id\":\"60af6c339d9698f6496dae19\",\"vid\" : \"60fa618fd5a69d4f433ba058\"},\"ppid\" : 8612,\"ruleInfo\" : {\"pathInfo\":{\"type\":0,\"value\" : \"C:\\TEMP\\HOST\\NOTEPAD.EXE\"},\"ruleUUID\" : \"60fa618fd5a69dfcfe3ba052\"},\"trustInfo\" : {\"positives\":0,\"score\" : 100,\"total\" : 50},\"username\" : \"INCT-BINDUK\\bindu.k\" }");
    LPCSTR ptr = temp.c_str();

    DWORD dwEventDataSize = ((DWORD)(temp.length() + 1) * sizeof(CHAR));
    ReportEventA(event_log, EVENTLOG_WARNING_TYPE, DATABASE_CATEGORY, MSG_INVALID_COMMAND, NULL, 1, 0, &ptr, NULL);
   /* ReportEventA(event_log, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, &ptr, NULL);

    temp = "Warning Log";
    ptr = temp.c_str();
    ReportEvent(event_log, EVENTLOG_WARNING_TYPE, 0, 0, NULL, 1, 0, &ptr, NULL);

    temp = "Error Log";
    ptr = temp.c_str();
    ReportEvent(event_log, EVENTLOG_ERROR_TYPE, 0, 0, NULL, 1, 0, &ptr, NULL);
    

    HANDLE event_log = OpenEventLogA(NULL,custom_log_name);
    bool status = ClearEventLog(event_log, NULL);
    std::cout << "event log cleared : " << status << endl;*/
    return 0;
}