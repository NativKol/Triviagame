#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& fact, LoggedUser user, RoomManager& room_manage, Room room)
	: m_handleFactory(fact), m_user(user), m_roomManager(room_manage), m_room(room)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	if (info.id >= get_state_ && info.id <= leave_r_)
		return true;
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info, SOCKET clientSocket)
{
	ErrorResponse err_mes;
	err_mes.message = "Error!";

	std::vector<unsigned char> vec;
	if (isRequestRelevant(info))
	{
		switch (info.id)
		{
		case get_state_:
			return getRoomState(info);

		case leave_r_:
			return leaveRoom(info);
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	//this->m_room.removeUser(this->m_user);
	this->m_roomManager.getRoomInfo().find(m_room.getRoomData()._RoomId)->second->removeUser(this->m_user);
	MenuRequestHandler* menu = m_handleFactory.createMenuRequestHandler(this->m_user);
	RequestResult res;
	res.newHandler = &(*menu);

	LeaveRoomResponse leave;
	leave.status = 1;

	std::vector<unsigned char> vec;
	vec = JsonResponsePacketSerializer::serializeResponse(leave);
	res.response = vec;
	return res;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	GetRoomStateResponse state;
	RoomData data = this->m_room.getRoomData();
	state.hasGameBegun = data._Active;
	//state.players = this->m_room.getAllUsers();
	state.players = m_roomManager.getRoomInfo().find(m_room.getRoomData()._RoomId)->second->getAllUsers();

	state.answerTimeout = data._AvgTime;
	state.questionCount = data.numOfQuestionsInGame;
	state.status = 1;

	RequestResult res;
	res.newHandler = this;

	std::vector<unsigned char> vec = JsonResponsePacketSerializer::serializeResponse(state);
	res.response = vec;
	return res;
}