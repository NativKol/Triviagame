#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string m_username, SOCKET s)
{
	this->m_username = m_username;
	this->socket = s;
}

LoggedUser LoggedUser::getUser()
{
	return *this;
}

std::string LoggedUser::getUsername()
{
	return this->m_username;
}

SOCKET LoggedUser::get_socket()
{
	return socket;
}