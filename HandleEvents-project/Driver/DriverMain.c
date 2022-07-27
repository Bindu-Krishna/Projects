#pragma once
/************************************************/
/*  Register call back functions */
/* Initialise needed resources */

NTSTATUS GetPreCreateNotification(p_callback_data, input_obj )
{
    // Read the rules stored in a list
    // Apply the rules and check if access should be blocked
    // form a alert structure if ACCESS_DENIED
    // Send the alert to user space via IOCTL
    // p_callback_data.access = ACCESS_DENIED;
    return NT_SUCCESS;
}