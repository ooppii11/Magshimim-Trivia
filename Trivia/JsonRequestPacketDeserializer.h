#pragma once
#include "Request.h"
#include "BufferDeserializer.hpp"

class Deserializer
{
public:
	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(const Buffer& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer& buffer);

	static AddCategorieRequest addCategorieToUser(const Buffer& buffer);
	static RemoveCategorieRequest removeCategorieFromUser(const Buffer& buffer);
	static AddQuestionRequest addQuestionToUserCategorie(const Buffer& buffer);
	static RemoveQuestionRequest removeQuestionFromUserCategorie(const Buffer& buffer);

	static SubmitAnswerRequest deserializeSubminAnswerRequest(const Buffer& buffer);

	static UserKey deserializeSubminUserKey(const Buffer& buffer);

};