#pragma once
#include <string>
#include <vector>

enum RequestCodes 
{
	SIGNUP_REQUEST_CODE = 1,
	LOGIN_REQUEST_CODE,
	LOGOUT_REQUEST_CODE,
	GET_ROOMS_REQUEST_CODE,
	GET_PLAYERS_IN_ROOM_REQUEST_CODE,
	HIGH_SCORE_REQUEST_CODE,
	PERSONAL_STATS_REQUEST_CODE,
	JOIN_ROOM_REQUEST_CODE,
	CREATE_ROOM_REQUEST_CODE
};

#define NUM_OF_ANSWERS 4

typedef struct LoginRequest
{
	std::string username;
	std::string password;
}LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
}SignupRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}CreateRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
}JoinRoomRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
}GetPlayersInRoomRequest;

typedef struct addCategorie
{
	std::string categorieName;
	bool permission;
}addCategorie;

typedef struct removeCategorie
{
	std::string categorieName;
}removeCategorie;

typedef struct addQuestion
{
	std::string categorieName;
	std::string questionName;
	unsigned int correctAnswerIndex;
	std::vector<std::string> answers;
	addQuestion() : correctAnswerIndex(0)
	{
		answers.resize(NUM_OF_ANSWERS);
	}
}addQuestion;

typedef struct removeQuestion
{
	std::string categorieName;
	std::string questionName;
}removeQuestion;