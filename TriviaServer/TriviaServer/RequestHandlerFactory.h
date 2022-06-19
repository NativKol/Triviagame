#pragma once
#include "LoginRequestHandler.h"
#include "IDataAccess.h"
#include "LoginManager.h"
#include "SqliteDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDataAccess& dataAccess, StatisticsManager stats);
	//~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler(); //
	LoginManager& getLoginManager(); //

	MenuRequestHandler* createMenuRequestHandler(LoggedUser logged);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room room);
private:
	IDataAccess* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;
};