#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"
#include "LoggedUser.h"
class LoggedUser;
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& fact,LoginManager& manage, LoggedUser user, RoomManager& room);
	virtual bool isRequestRelevant(RequestInfo info);
	virtual RequestResult handleRequest(RequestInfo info, SOCKET clientSocket);

private:
	LoginManager& m_loginManager;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
	LoggedUser m_user;

	RequestResult logout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRooms(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
};