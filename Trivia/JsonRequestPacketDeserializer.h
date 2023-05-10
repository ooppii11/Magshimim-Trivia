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
	static addCategorie addCategorieToUser(const Buffer& buffer);
	static removeCategorie removeCategorieFromUser(const Buffer& buffer);
	static addQuestion addQuestionToUserCategorie(const Buffer& buffer);
	static removeQuestion removeQuestionFromUserCategorie(const Buffer& buffer);
};