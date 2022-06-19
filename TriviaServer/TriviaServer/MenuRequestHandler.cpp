#include "MenuRequestHandler.h"
extern int id_count;
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& fact, LoginManager& manage, LoggedUser user, RoomManager& room) 
	: m_handleFactory(fact), m_roomManager(room),
	m_loginManager(manage), m_user(user)
{
	//m_roomManager = RoomManager();
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id >= logout_ && info.id <= getPersonalStats_)
		return true;
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info, SOCKET clientSocket)
{
	ErrorResponse err_mes;
	err_mes.message = "Error!";
	std::cout << info.id << std::endl;
	std::vector<unsigned char> vec;
	if (isRequestRelevant(info))
	{
		switch (info.id)
		{
		case logout_:
			return logout(info);

		case join_:
			return joinRoom(info);

		case create_:
			return createRoom(info);

		case getRoom_:
			return getRooms(info);

		case getPlayers_:
			return getPlayersInRooms(info);

		case getHighScore_:
			return getHighScore(info);

		case getPersonalStats_:
			return getPersonalStats(info);
		break;
		}
	}
	else
		vec = JsonResponsePacketSerializer::serializeResponse(err_mes);
	RequestResult result;
	result.response = vec;
	result.newHandler = nullptr;
	return result;
}

RequestResult MenuRequestHandler::logout(RequestInfo info)
{
	LogoutResponse log_mes;
	RequestResult res;
	//LoginRequest log_req = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

	if (m_loginManager.LogOut(m_user.getUsername()))
	{
		log_mes.status = 1;
		res.newHandler = m_handleFactory.createLoginRequestHandler();
	}
	else
	{
		log_mes.status = 0;
		res.newHandler = this;
	}

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(log_mes);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo)
{
	GetRoomsResponse get_r;
	get_r.rooms = m_roomManager.getRooms();
	get_r.status = 1;

	RequestResult res;
	res.newHandler = this;

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(get_r);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::getPlayersInRooms(RequestInfo info)
{
	GetPlayersInRoomResponse get_play;
	GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayesRequest(info.buffer);
	//auto it = m_roomManager.getRoomInfo().find(int(req.roomId));
	//if (it != m_roomManager.getRoomInfo().end())
	//	get_play.players = it->second->getAllUsers();
	get_play.players = m_roomManager.getRoomInfo().find(req.roomId)->second->getAllUsers();
	RequestResult res;
	res.newHandler = this;

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(get_play);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo)
{
	RequestResult res;
	res.newHandler = this;

	GetPersonalStatsResponse get_ps;
	get_ps.status = 1;
	get_ps.statistics = m_handleFactory.getStatisticsManager().getUserStatistics(m_user.getUsername());

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(get_ps);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo)
{
	RequestResult res;
	res.newHandler = this;

	GetHighScoreResponse get_hs;
	get_hs.status = 1;
	get_hs.statistics = m_handleFactory.getStatisticsManager().getHighScore();

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(get_hs);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomResponse join_res;
	join_res.status = 0;

	JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);

	if(m_roomManager.getRoomInfo().find(req.roomId)->second->addUser(m_user.getUser()))
		join_res.status = 1;
	
	RequestResult res;
	res.newHandler = m_handleFactory.createRoomMemberRequestHandler(m_user, *(m_roomManager.getRoomInfo().find(req.roomId)->second));

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(join_res);
	res.response = vec;
	return res;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	CreateRoomResponse create_res;
	create_res.status = 1;
	CreateRoomRequest create = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);

	RoomData new_data;
	new_data._Active = 0;
	new_data._AvgTime = create.answerTimeout;
	new_data._MaxPlayers = create.maxUsers;
	new_data._RoomId = id_count;
	create_res.status = id_count;			//return room id
	new_data._RoomName = create.roomName;
	new_data.numOfQuestionsInGame = create.questionCount;
	Room new_room = m_roomManager.createRoom(this->m_user, new_data);

	RequestResult res;
	res.newHandler = this->m_handleFactory.createRoomAdminRequestHandler(this->m_user, new_room);

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(create_res);
	res.response = vec;
	return res;
}
