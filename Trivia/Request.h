#pragma once
#include <string>
#include <vector>
#define SIGNUP_REQUEST_CODE 1
#define LOGIN_REQUEST_CODE 2
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

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}CreateRoomRequest;

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