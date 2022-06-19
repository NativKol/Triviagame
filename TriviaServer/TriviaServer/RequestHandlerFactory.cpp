#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataAccess& dataAccess, StatisticsManager stats) : m_database(&dataAccess)
	, m_StatisticsManager(stats)
{
	this->m_loginManager = LoginManager(&dataAccess);
	this->m_roomManager = RoomManager();
}

//RequestHandlerFactory::~RequestHandlerFactory()
//{
//	m_database->close();
//}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() //
{
	LoginRequestHandler* login_han = new LoginRequestHandler(*this, this->getLoginManager());
	return login_han;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser logged)
{
	MenuRequestHandler* menu_han = new MenuRequestHandler(*this, this->getLoginManager(), logged, this->getRoomManager());
	return menu_han;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room room)
{
	RoomAdminRequestHandler* admin_han = new RoomAdminRequestHandler(*this, user, this->m_roomManager, room);
	return admin_han;
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room room)
{
	RoomMemberRequestHandler* member_han = new RoomMemberRequestHandler(*this, user, this->m_roomManager, room);
	return member_han;
}