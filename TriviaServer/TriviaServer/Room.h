#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "LoggedUser.h"


typedef struct {
	unsigned int _RoomId;
	std::string _RoomName;
	unsigned int _MaxPlayers;
	unsigned int _AvgTime;
	unsigned int _Active;
	unsigned int numOfQuestionsInGame;
}RoomData;

class Room
{
public:
	Room(unsigned int RoomId, std::string RoomName, unsigned int MaxPlayers, unsigned int AvgTime, unsigned int Active);
	~Room();

	bool addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	std::vector<LoggedUser> get_sockets();
	unsigned int getRoomState();
	RoomData getRoomData();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;		//change to LoggedUser

};
