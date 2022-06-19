#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"
#include "LoggedUser.h"
#include "Room.h"
class RequestHandlerFactory;
class Room;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& fact, LoggedUser user, RoomManager& room_manage, Room room);
	virtual bool isRequestRelevant(RequestInfo info);
	virtual RequestResult handleRequest(RequestInfo info, SOCKET clientSocket);

	RequestResult getRoomState(RequestInfo info);
private:
	Room m_room;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
	LoggedUser m_user;

	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
};