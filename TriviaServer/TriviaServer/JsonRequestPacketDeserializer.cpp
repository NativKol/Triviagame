#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> request_vec)
{
	LoginRequest req;

	json j = json::parse(request_vec.begin() + 5, request_vec.end());
	//std::string str_res = j.dump();
	req.password = j["password"];
	req.username = j["username"];
	return req;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> request_vec)
{
	SignupRequest req;

	json j = json::parse(request_vec.begin() + 5, request_vec.end()); 
	//std::string str_res = j.dump();
	req.email = j["email"];
	req.password = j["password"];
	req.username = j["username"];
	return req;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayesRequest(std::vector<unsigned char> request_vec)
{
	GetPlayersInRoomRequest req;

	json j = json::parse(request_vec.begin() + 5, request_vec.end());
	//std::string str_res = j.dump();
	req.roomId = j["id"];
	return req;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> request_vec)
{
	JoinRoomRequest req;

	json j = json::parse(request_vec.begin() + 5, request_vec.end());
	//std::string str_res = j.dump();
	req.roomId = j["id"];
	return req;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> request_vec)
{
	CreateRoomRequest req;

	json j = json::parse(request_vec.begin() + 5, request_vec.end());
	//std::string str_res = j.dump();
	req.roomName = j["name"];
	req.questionCount = j["question_count"];
	req.maxUsers = j["max_users"];
	req.answerTimeout = j["answer_timeout"];
	return req;
}
