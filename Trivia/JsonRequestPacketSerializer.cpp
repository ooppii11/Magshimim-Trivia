#include "JsonRequestPacketSerializer.hpp"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

//json.dump()
/*
Json::StyledWriter styledWriter;
Json::FastWriter fastWriter;
Json::Value newValue;
newValue["key"] = value;

styledWriter.write(newValue);
fastWriter.write(newValue);
*/

Buffer Serializer::serializeResponse(const ErrorResponse& response)
{
	Buffer temp;
	json data;
	data["Error"] = response.message;
	temp.header = response.status;
    temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const LoginResponse& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(const SignupResponse& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(const LogoutResponse& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(const GetRoomsResponse& response)
{
	Buffer temp;
	json data;
	data["Rooms"] = Serializer::vectorToString(response.rooms);
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
	Buffer temp;
	json data;
	data["PlayersInRoom"] = response.rooms;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const getHighScoreResponse& response)
{
	Buffer temp;
	json data;
	data["HighScores"] = response.statistics;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const JoinRoomResponse& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(const CreateRoomResponse& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(const getPersonalStatsResponse& response)
{
	Buffer temp;
	json data;
	data["UserStatistics"] = response.statistics;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

