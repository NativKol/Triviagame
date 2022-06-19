#pragma once
#include "IRequestHandler.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
class IRequestHandler;

struct SignupRequest
{
    std::string username;
    std::string password;
    std::string email;
};

struct RequestResult
{
    std::vector<unsigned char> response;
    IRequestHandler* newHandler;
};

struct RequestInfo
{
    int id;
    std::time_t receivalTime;
    std::vector<unsigned char> buffer;
};

struct LoginRequest
{
    std::string username;
    std::string password;
};

struct GetPlayersInRoomRequest
{
    unsigned int roomId;
};

struct JoinRoomRequest
{
    unsigned int roomId;
};

struct CreateRoomRequest
{
    std::string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;
};