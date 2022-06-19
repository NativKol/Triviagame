#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& fact, LoggedUser user, RoomManager& room_manage, Room room);
	virtual bool isRequestRelevant(RequestInfo info);
	virtual RequestResult handleRequest(RequestInfo info, SOCKET clientSocket);

private:
	Room m_room;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handleFactory;
	LoggedUser m_user;

	RequestResult leaveRoom(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

};