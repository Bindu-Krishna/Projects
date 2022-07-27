#pragma once
#include <iostream>
#include <string.h>
/**************************************************************************/
/*  Header file to accomodate for all HTTP / HTTPS related helper functions */
/**************************************************************************/

/* fxn 1 : Send HTTP data */
bool SendData(void* p_data, std::string p_route, ServerResponse* p_respose);
