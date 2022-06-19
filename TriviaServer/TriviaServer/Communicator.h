#pragma once
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "RequestHandlerFactory.h"
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>
#include <string>
//#include <thread>
#include <map>
//#include "responseStruct.h"
//#include "JsonRequestPacketDeserializer.h"
#include "IDataAccess.h"
//#include "json.hpp"
//#include <queue>
class RequestHandlerFactory;

#define USERSTART 5
#define NAMESTART 2
#define ASCI_TO_INT 48
#define LEN_OF_MESSAGE 100

#define min(a,b) ((a) < (b) ? (a) : (b))

class Communicator
{
public:
	Communicator(IDataAccess* dataAccess, RequestHandlerFactory& fact);
	~Communicator();
	void handle_messages(int port);
	void startHandleRequest(SOCKET clientSocket);
	std::string convertToString(char* a, int start, int end);

private:
	void bindAndListen(int port);
	void handleNewClient(SOCKET clientSocket);

	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	SOCKET _serverSocket;
};
#endif