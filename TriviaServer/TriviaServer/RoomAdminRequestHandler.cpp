#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& fact, LoggedUser user, RoomManager& room_manage, Room room)
	: m_handleFactory(fact), m_user(user), m_roomManager(room_manage), m_room(room)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id >= close_r_ && info.id <= get_state_)
		return true;
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info, SOCKET clientSocket)
{
	ErrorResponse err_mes;
	err_mes.message = "Error!";

	std::vector<unsigned char> vec;
	if (isRequestRelevant(info))
	{
		switch (info.id)
		{
		case close_r_:
			return closeRoom(info);

		case start_g_:
			return startGame(info);

		case get_state_:
			return getRoomState(info);
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	MenuRequestHandler* menu = this->m_handleFactory.createMenuRequestHandler(m_user);
	AdminLeaveRoomResponse leave;
	leave.status = 1;
	RequestResult res;
	res.newHandler = &(*menu);

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(leave);

	std::vector<char> newOne = std::vector<char>(vec.begin(), vec.end()); //to send
	for (auto i : m_room.get_sockets())
	{
		if (i.get_socket() != this->m_user.get_socket())
			send(i.get_socket(), &newOne[0], vec.size(), 0);
	}

	//creating this admin response
	CloseRoomResponse close;
	close.status = 1;
	vec = JsonResponsePacketSerializer::serializeResponse(close);

	res.response = vec;
	this->m_roomManager.deleteRoom(this->m_room.getRoomData()._RoomId);
	return res;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	StartGameResponse start;
	start.status = 1;
	RequestResult res;
	res.newHandler = this;

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(start);

	std::vector<char> newOne = std::vector<char>(vec.begin(), vec.end()); //to send
	for (auto i : m_room.get_sockets())
	{
		if (i.get_socket() != this->m_user.get_socket())
			send(i.get_socket(), &newOne[0], vec.size(), 0);
	}

	//creating this admin response
	res.response = vec;
	return res;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
	GetRoomStateResponse state;
	RoomData data = this->m_room.getRoomData();
	state.hasGameBegun = data._Active;
	//state.players = this->m_room.getAllUsers();
	state.players = this->m_roomManager.getRoomInfo().find(m_room.getRoomData()._RoomId)->second->getAllUsers();
	state.answerTimeout = data._AvgTime;
	state.questionCount = data.numOfQuestionsInGame;
	state.status = 1;

	RequestResult res;
	res.newHandler = this;

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(state);
	res.response = vec;
	return res;
}