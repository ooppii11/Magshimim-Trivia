#pragma once
#pragma once
#include "Response.h"
#include "BufferDeserializer.hpp"

class Serializer
{
public:
	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);
	static Buffer serializeResponse(LogoutResponse response);
	static Buffer serializeResponse(GetRoomsResponse response);
	static Buffer serializeResponse(GetPlayersInRoomResponse response);
	static Buffer serializeResponse(JoinRoomResponse response);
	static Buffer serializeResponse(CreateRoomResponse response);
	static Buffer serializeResponse(getHighScoreResponse response);
	static Buffer serializeResponse(getPersonalStatsResponse response);
};