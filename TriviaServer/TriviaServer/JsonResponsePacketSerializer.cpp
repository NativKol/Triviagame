#include "JsonResponsePacketSerializer.h"
using json = nlohmann::json;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	json j = { {"message", err.message} };
	unsigned char code = (unsigned char)Error_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse sign)
{
	json j = { {"status", sign.status} };
	unsigned char code = (unsigned char)signup_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	json j = { {"status", log.status} };
	unsigned char code = (unsigned char)login_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse log)
{
	json j = { {"status", log.status} };
	unsigned char code = (unsigned char)logout_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse get_r)
{
	json j = { {"status", get_r.status} };
	
	for (int i = 0; i < get_r.rooms.size(); i++)
	{
		json jj;
		jj["id"] = get_r.rooms[i]._RoomId;
		jj["name"] = get_r.rooms[i]._RoomName;
		j["rooms"].push_back(jj);
	}
	unsigned char code = (unsigned char)getRoom_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse get_p)
{
	json j = { {"status", 1} };

	for (int i = 0; i < get_p.players.size(); i++)
	{
		/*json jj;
		jj["id"] = get_r.rooms[i]._RoomId;
		jj["name"] = get_r.rooms[i]._RoomName;*/
		j["rooms"].push_back(get_p.players[i]);
	}
	unsigned char code = (unsigned char)getPlayers_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse join)
{
	json j = { {"status", join.status} };
	unsigned char code = (unsigned char)join_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse create)
{
	json j = { {"status", create.status} };
	unsigned char code = (unsigned char)create_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse get_h)
{
	json j = { {"status", get_h.status} };

	for (int i = 0; i < get_h.statistics.size(); i++)
	{
		j["HighScores"].push_back(get_h.statistics[i]);
	}
	unsigned char code = (unsigned char)getHighScore_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse get_ps)
{
	json j = { {"status", get_ps.status} };

	for (int i = 0; i < get_ps.statistics.size(); i++)
	{
		j["Personal Stats"].push_back(get_ps.statistics[i]);
	}
	unsigned char code = (unsigned char)getPersonalStats_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::helper(json j, int code)
{
	//unsigned char zer = '0';
	std::vector<unsigned char> res;
	res.push_back((unsigned char)code);
	std::string str_res = j.dump();

	int size = str_res.size();
	/*std::string size = std::to_string(str_res.size());
	for (int i = 0; i < size.size(); i++)
		res.push_back(size[i]);*/
	res.push_back(size);
	while (res.size() < 5)
		res.push_back(NULL);

	res.insert(res.end(), str_res.begin(), str_res.end());
	return res;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse close_r)
{
	json j = { {"status", close_r.status} };
	unsigned char code = (unsigned char)close_r_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse start_g)
{
	json j = { {"status", start_g.status} };
	unsigned char code = (unsigned char)start_g_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse get_state)
{
	json j = { {"status", get_state.status} };

	j["hasGameBegun"] = get_state.hasGameBegun;

	for (int i = 0; i < get_state.players.size(); i++)
	{
		j["players"].push_back(get_state.players[i]);
	}
	j["answerTimeout"] = get_state.answerTimeout;

	j["numOfQuestionsInGame"] = get_state.questionCount;

	unsigned char code = (unsigned char)getPersonalStats_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leave_r)
{
	json j = { {"status", leave_r.status} };
	unsigned char code = (unsigned char)leave_r_;
	return JsonResponsePacketSerializer::helper(j, code);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(AdminLeaveRoomResponse admin_leave_r)
{
	json j = { {"status", admin_leave_r.status} };
	unsigned char code = '>';
	return JsonResponsePacketSerializer::helper(j, code);

}