#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

struct RequestInfo
{
    int id;
    std::time_t receivalTime;
    std::vector<unsigned char> buffer;
};