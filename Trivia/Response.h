#pragma once
#include <string>
#include <vector>
#include "Room.h"
#include "IDatabase.h"
#include <map>
#include <algorithm>


enum ResponseCodes {
	SIGNUP_AND_LOGIN_RESPONSE_CODE = 1,
	LOGOUT_RESPONSE_CODE,
	GET_ROOMS_RESPONSE_CODE,
	GET_PLAYERS_IN_ROOM_RESPONSE_CODE,
	HIGH_SCORE_RESPONSE_CODE,
	GET_PUBLIC_CATEGORIES_RESPONSE_CODE,
	GET_PRIVATE_CATEGORIES_RESPONSE_CODE,
	PERSONAL_STATS_RESPONSE_CODE,
	GET_USER_HISTORY_RESPONSE_CODE,
	JOIN_ROOM_RESPONSE_CODE,
	CREATE_ROOM_RESPONSE_CODE,
	ADD_CATEGORIE_RESPONSE_CODE,
	REMOVE_CATEGORIE_RESPONSE_CODE,
	ADD_QUESTION_RESPONSE_CODE,
	REMOVE_QUESTION_RESPONSE_CODE,
	CLOSE_ROOM_RESPONSE_CODE,
	START_GAME_RESPONSE_CODE,
	GET_ROOM_STATE_RESPONSE_CODE,
	LEAVE_ROOM_RESPONSE_CODE,
	LEAVE_GAME_RESPONSE_CODE,
	GET_QUESTION_RESPONSE_CODE,
	SUBMIT_ANSWER_RESPONSE_CODE,
	GET_GAME_RESULTS_RESPONSE_CODE,

	ERROR_RESPONSE_CODE = 99
};

typedef struct OnlyStatus
{
	unsigned int status;
	OnlyStatus(unsigned int code) : status(code) {}
}OnlyStatus;

typedef struct LoginResponse : OnlyStatus
{
	LoginResponse() : OnlyStatus(SIGNUP_AND_LOGIN_RESPONSE_CODE) {}
}LoginResponse;

typedef struct SignupResponse : OnlyStatus
{
	SignupResponse() : OnlyStatus(SIGNUP_AND_LOGIN_RESPONSE_CODE) {}
}SignupResponse;

typedef struct ErrorResponse
{
	unsigned int status;
	std::string message;
	ErrorResponse() : message(""), status(ERROR_RESPONSE_CODE) {}
	ErrorResponse(char* msg) : message(msg), status(ERROR_RESPONSE_CODE) {}
	ErrorResponse(std::string msg) : message(msg), status(ERROR_RESPONSE_CODE) {}
}ErrorResponse;

typedef struct LogoutResponse : OnlyStatus
{
	LogoutResponse() : OnlyStatus(LOGOUT_RESPONSE_CODE){}
}LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
	GetRoomsResponse() : status(GET_ROOMS_RESPONSE_CODE) {}
}GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	unsigned int status;
	std::vector<std::string> rooms;
	GetPlayersInRoomResponse() : status(GET_PLAYERS_IN_ROOM_RESPONSE_CODE) {}
}GetPlayersInRoomResponse;

typedef struct getHighScoreResponse
{
	unsigned int status;
	std::map<std::string, int> statistics;
	getHighScoreResponse() : status(HIGH_SCORE_RESPONSE_CODE) {}
}getHighScoreResponse;

typedef struct getPersonalStatsResponse
{
	unsigned int status;
	std::map<std::string, int> statistics;
	getPersonalStatsResponse() : status(PERSONAL_STATS_RESPONSE_CODE) {}
}getPersonalStatsResponse;
//
typedef struct getUserHistory
{
	unsigned int status;
	std::vector<History> history;
	getUserHistory() : status(GET_USER_HISTORY_RESPONSE_CODE) {}
}getUserHistory;

typedef struct getPublicCategoriesResponse
{
	unsigned int status;
	std::map<int, std::string> publicCategories;
	getPublicCategoriesResponse() : status(GET_PUBLIC_CATEGORIES_RESPONSE_CODE) {}
}getPublicCategoriesResponse;

typedef struct getPrivateCategoriesResponse
{
	unsigned int status;
	std::map<int, std::string> PrivateCategories;
	getPrivateCategoriesResponse() : status(GET_PRIVATE_CATEGORIES_RESPONSE_CODE) {}
}getPrivateCategoriesResponse;

typedef struct JoinRoomResponse : OnlyStatus
{
	JoinRoomResponse() : OnlyStatus(JOIN_ROOM_RESPONSE_CODE) {}
}JoinRoomResponse;

typedef struct CreateRoomResponse 
{
	unsigned int status;
	unsigned int roomId;
	CreateRoomResponse() : status(CREATE_ROOM_RESPONSE_CODE) {}
}CreateRoomResponse;

typedef struct AddCategorieResponse : OnlyStatus
{
	AddCategorieResponse() : OnlyStatus(ADD_CATEGORIE_RESPONSE_CODE) {}
}addCategorieResponse;

typedef struct RemoveCategorieResponse : OnlyStatus
{
	RemoveCategorieResponse() : OnlyStatus(REMOVE_CATEGORIE_RESPONSE_CODE) {}
}removeCategorieResponse;

typedef struct AddQuestionResponse : OnlyStatus
{
	AddQuestionResponse() : OnlyStatus(ADD_QUESTION_RESPONSE_CODE) {}
}addQuestionResponse;

typedef struct RemoveQuestionResponse : OnlyStatus
{
	RemoveQuestionResponse() : OnlyStatus(REMOVE_QUESTION_RESPONSE_CODE) {}
}removeQuestionResponse;

typedef struct CloseRoomResponse : OnlyStatus
{
	CloseRoomResponse() : OnlyStatus(CLOSE_ROOM_RESPONSE_CODE) {}
}CloseRoomResponse;

typedef struct StartGameResponse : OnlyStatus
{
	StartGameResponse() : OnlyStatus(START_GAME_RESPONSE_CODE) {}
}StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
	GetRoomStateResponse() : status(GET_ROOM_STATE_RESPONSE_CODE) {}
}GetRoomStateResponse;

typedef struct LeaveRoomResponse : OnlyStatus
{
	LeaveRoomResponse() : OnlyStatus(LEAVE_ROOM_RESPONSE_CODE) {}
}LeaveRoomResponse;

typedef struct LeaveGameResponse : OnlyStatus
{
	LeaveGameResponse() : OnlyStatus(LEAVE_GAME_RESPONSE_CODE) {}
}LeaveGameResponse;

typedef struct GetQuestionResponse
{
	unsigned int status;
	std::string question;
	std::map<unsigned int, std::string> answers;
	GetQuestionResponse() : status(GET_QUESTION_RESPONSE_CODE) {}
}GetQuestionResponse;

typedef struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerIndex;
	SubmitAnswerResponse() : status(SUBMIT_ANSWER_RESPONSE_CODE) {}
}SubmitAnswerResponse;

typedef struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	double averageAnswerTime;
	friend std::ostream& operator<<(std::ostream& os, const PlayerResults& data);
}PlayerResults;

typedef struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
	GetGameResultsResponse() : status(GET_GAME_RESULTS_RESPONSE_CODE) {}
}GetGameResultsResponse;

typedef struct PublicKey
{
	std::map<std::string, std::string> key;
}PublicKey;

