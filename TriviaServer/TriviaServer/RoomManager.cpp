#include "RoomManager.h"
extern int id_count;

RoomManager::RoomManager()
{
	this->_AmountOoRooms = 0;
	this->m_rooms = new std::map<int, Room*> ();
}

RoomManager::~RoomManager()
{
	this->_AmountOoRooms = 0;
	//this->m_rooms->clear();
}

Room RoomManager::createRoom(LoggedUser name, RoomData data)
{
	//std::map<int, int> check;
	//check.clear();
	Room* r = new Room(data._RoomId, data._RoomName, data._MaxPlayers, data._AvgTime, data._Active);
	r->addUser(name);
	//std::pair<int, Room*> pair_toInsert(id_count, &r);
	//this->m_rooms->clear();
	this->m_rooms->insert({id_count, r});
	_AmountOoRooms++;
	id_count++;
	return *r;
}

void RoomManager::deleteRoom(int ID)
{
	this->m_rooms->erase(ID);
	this->_AmountOoRooms--;
}

unsigned int RoomManager::getRoomState(int ID)
{
	auto it = this->m_rooms->find(ID);
	return it->second->getRoomState();
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> copy;
	if (this->m_rooms->size() == 0)
		return copy;
	auto iter = this->m_rooms->begin();
	while (iter != this->m_rooms->end())
	{
		copy.push_back(iter->second->getRoomData());
		++iter;
	}
	return copy;
}

std::map<int, Room*> RoomManager::getRoomInfo()
{
	return *this->m_rooms;
}
