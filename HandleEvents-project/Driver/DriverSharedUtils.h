#pragma once
/*****************************************/
/* This header file is common to both user space and driver */

/* Place holder to store the data related to alerts */
/* This data is filled in the driver and used by the user space process */

/* Since drivers are written in C language, we should be defining the needed structs / enums if any */

typedef enum _FILE_PERMISSIONS {
    ACCESS_DENIED = 0,
    ACCESS_ALLOWED,
    INVALID
}FILE_PERMISSIONS;

typedef enum _ACCESS_REQUESTED {
    READ = 0,
    WRITE,
    DELETE,
    CREATE, //....
    INVALID
}ACCESS_REQUESTED;

struct _file_alert_data 
{
    int m_pid;
    int m_fileName;
    ACCESS_REQUESTED m_access_requested;
    FILE_PERMISSIONS m_access;
    // .....
}file_alert_data;