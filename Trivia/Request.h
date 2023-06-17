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
	GET_PUBLIC_CATEGORIES_REQUEST_CODE,
	GET_PRIVATE_CATEGORIES_REQUEST_CODE,
	PERSONAL_STATS_REQUEST_CODE,
	GET_USER_HISTORY_REQUEST_CODE,
	JOIN_ROOM_REQUEST_CODE,
	CREATE_ROOM_REQUEST_CODE,
	ADD_CATEGORIE_REQUEST_CODE,
	REMOVE_CATEGORIE_REQUEST_CODE,
	ADD_QUESTION_REQUEST_CODE,
	REMOVE_QUESTION_REQUEST_CODE,
	CLOSE_ROOM_REQUEST_CODE,
	START_GAME_REQUEST_CODE,
	GET_ROOM_STATE_REQUEST_CODE,
	LEAVE_ROOM_REQUEST_CODE,
	SUBMIT_ANSWER_REQUEST_CODE,
	LEAVE_GAME_REQUEST_CODE,
	GET_QUESTION_REQUEST_CODE,
	GET_GAME_RESULT_REQUEST_CODE,
	
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
	unsigned int categorieId;
}CreateRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
}JoinRoomRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
}GetPlayersInRoomRequest;

typedef struct AddCategorieRequest
{
	std::string categoryName;
	bool permission;
}addCategorieRequest;

typedef struct RemoveCategorieRequest
{
	unsigned int categorieId;
}removeCategorieRequest;

typedef struct AddQuestionRequest
{
	unsigned int categorieId;
	std::string questionName;
	unsigned int correctAnswerIndex;
	std::vector<std::string> answers;
	AddQuestionRequest() : correctAnswerIndex(0), categorieId(0)
	{
		answers.resize(NUM_OF_ANSWERS);
	}
}addQuestionRequest;

typedef struct RemoveQuestionRequest
{
	unsigned int categorieId;
	std::string questionName;
}removeQuestionRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerIndex;
}SubmitAnswerRequest;
