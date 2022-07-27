#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

using namespace std;
//move this to global intialiser class
extern HANDLE g_input_sem ;
extern HANDLE g_op_complete_sem ;
extern BOOL g_is_input_list_full;
extern mutex g_input_list_mutex;
extern vector<string> g_input_list;

void client(std::vector<string> l_paths);
void server();

enum class ProcessingStatus {
    SUCCESS = 0,
    FAILURE = 1,
    NO_INPUT = 2,
    INVALID = 9999
};