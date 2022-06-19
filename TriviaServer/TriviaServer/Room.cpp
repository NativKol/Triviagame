#include "Room.h"

Room::Room(unsigned int RoomId, std::string RoomName, unsigned int MaxPlayers, unsigned int AvgTime, unsigned int Active)
{
	this->m_metadata._AvgTime = AvgTime;
	this->m_metadata._Active = Active;
	this->m_metadata._MaxPlayers = MaxPlayers;
	this->m_metadata._RoomId = RoomId;
	this->m_metadata._RoomName = RoomName;
	this->m_users.clear();
}

Room::~Room()
{
	this->m_metadata._AvgTime = 0;
	this->m_metadata._Active = 0;
	this->m_metadata._MaxPlayers = 0;
	this->m_metadata._RoomId = 0;
	this->m_metadata._RoomName = "";
	this->m_users.clear();
}

bool Room::addUser(LoggedUser user) 
{
	if (this->getAllUsers().size() < this->getRoomData()._MaxPlayers)
		this->m_users.push_back(user);
	else
		return false;
	return true;
	//this->m_socket.insert(std::make_pair(s, user.getUsername()));
}
void Room::removeUser(LoggedUser user)
{
	int j = 0;
	int size = m_users.size();

	for (auto& i : m_users)
	{
		if (i.getUsername() == user.getUsername())
		{
			m_users.erase(m_users.begin() + j);
			return;
		}
		j++;
	}

}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> copy;
	for (auto i : this->m_users)
		copy.push_back(i.getUsername());
	return copy;
}

unsigned int Room::getRoomState()
{
	return this->m_metadata._Active;
}

RoomData Room::getRoomData()
{
	return this->m_metadata;
}

std::vector<LoggedUser> Room::get_sockets()
{
	return m_users;
}