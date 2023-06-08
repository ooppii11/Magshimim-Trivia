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
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const SignupResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const LogoutResponse& response)
{
	return Serializer::setStatus(response);
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
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const CreateRoomResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const getPersonalStatsResponse& response)
{
	Buffer temp;
	json data;
	data["statistics"] = response.statistics;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const getPublicCategoriesResponse& response)
{
	Buffer temp;
	json data;
	data["publicCategories"] = response.publicCategories;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const getPrivateCategoriesResponse& response)
{
	Buffer temp;
	json data;
	data["PrivateCategories"] = response.PrivateCategories;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const AddCategorieResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const RemoveCategorieResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const AddQuestionResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const RemoveQuestionResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const getUserHistory& response)
{
	Buffer temp;
	json data;
	data["History"] = Serializer::vectorToString(response.history);
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::setStatus(const OnlyStatus& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}
