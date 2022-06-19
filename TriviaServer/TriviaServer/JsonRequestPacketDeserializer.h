#pragma once
#include "requestStruct.h"
#include "responseStruct.h"
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char>);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char>);

	static GetPlayersInRoomRequest deserializeGetPlayesRequest(std::vector<unsigned char>);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char>);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char>);
};
