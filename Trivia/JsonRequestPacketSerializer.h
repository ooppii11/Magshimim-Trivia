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
	/*
	+ serializeResponse(LogoutResponse): Buffer
	+ serializeResponse(GetRoomsResponse) : Buffer
	+ serializerResponse(GetPlayersInRoomResponse) : Buffer
	+ serializeResponse(JoinRoomResponse) : Buffer
	+ serializeResponse(CreateRoomResponse) : Buffer
	+ serializeResponse(getHighScoreResponse) : Buffer
	+ serializeResponse(getPersonalStatsResponse) : Buffer

	*/
};