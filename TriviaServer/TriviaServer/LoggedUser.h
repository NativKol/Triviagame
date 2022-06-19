#ifndef LoggedUser_HEADER
#define LoggedUser_HEADER

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>

class LoggedUser
{
public:	
	LoggedUser(std::string m_username, SOCKET s);
	LoggedUser getUser();
	std::string getUsername();
	SOCKET get_socket();

private:
	std::string m_username;
	SOCKET socket;
};
#endif