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
	Buffer temp;
	json data;
	data["roomId"] = response.roomId;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
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


Buffer Serializer::serializeResponse(const CloseRoomResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const StartGameResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const GetRoomStateResponse& response)
{
	Buffer temp;
	json data;
	data["answerTimeout"] = response.answerTimeout;
	data["hasGameBegun"] = response.hasGameBegun;
	data["players"] = response.players;
	data["questionCount"] = response.questionCount;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const LeaveRoomResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::serializeResponse(const GetGameResultsResponse& response)
{
	Buffer temp;
	json data;
	data["Results"] = Serializer::vectorToString(response.results);
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const SubmitAnswerResponse& response)
{
	Buffer temp;
	json data;
	data["correctAnswerIndex"] = response.correctAnswerIndex;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const GetQuestionResponse& response)
{
	Buffer temp;
	json data;
	data["Answers"] = response.answers;
	data["Question"] = response.question;
	temp.header = response.status;
	temp.message = data.dump();
	return temp;
}

Buffer Serializer::serializeResponse(const LeaveGameResponse& response)
{
	return Serializer::setStatus(response);
}

Buffer Serializer::setStatus(const OnlyStatus& response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}
