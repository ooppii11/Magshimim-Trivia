#pragma once
#pragma once
#include "Response.h"
#include "BufferDeserializer.hpp"
#include <sstream>
#include <ostream>
#include <algorithm>

class Serializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);
	static Buffer serializeResponse(const LogoutResponse& response);
	static Buffer serializeResponse(const GetRoomsResponse& response);
	static Buffer serializeResponse(const GetPlayersInRoomResponse& response);
	static Buffer serializeResponse(const getHighScoreResponse& response);
	static Buffer serializeResponse(const JoinRoomResponse& response);
	static Buffer serializeResponse(const CreateRoomResponse& response);
	static Buffer serializeResponse(const getPersonalStatsResponse& response);
	static Buffer serializeResponse(const getPublicCategoriesResponse& response);
	static Buffer serializeResponse(const getPrivateCategoriesResponse& response);
	static Buffer serializeResponse(const AddCategorieResponse& response);
	static Buffer serializeResponse(const RemoveCategorieResponse& response);
	static Buffer serializeResponse(const AddQuestionResponse& response);
	static Buffer serializeResponse(const RemoveQuestionResponse& response);
	static Buffer serializeResponse(const CloseRoomResponse& response);
	static Buffer serializeResponse(const StartGameResponse& response);
	static Buffer serializeResponse(const GetRoomStateResponse& response);
	static Buffer serializeResponse(const LeaveRoomResponse& response);

private:
	template <typename T>
	static std::string vectorToString(const std::vector<T>& vec)
	{
		std::ostringstream oss;
		oss << "[";
		if (!vec.empty())
		{
			std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<T>(oss, ", "));
			oss << vec.back();
		}
		oss << "]";
		return oss.str();
	}

	static Buffer setStatus(const OnlyStatus& response);
};