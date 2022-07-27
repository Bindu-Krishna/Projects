#pragma once
#include <map>
#include <Bits.h>
#include <iostream>
#include <bitset>
#include <cassert>
#include <memory>

using namespace std;

enum class ProcessExtraInfoFlags {
    FINGERPRINT_CALC_FAILED = 0,
    NET_CONS_REPORTED = 1,
    SYSTEM_PROCESS = 2,
    HAS_VALID_IMAGE_PATH = 3,
    ALWAYS_ALLOW = 4,
    IN_WHITELIST = 5,
    BITSET_SIZE = 6
};
