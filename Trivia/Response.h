#pragma once
#include <string>
#include <vector>
#include "Room.h"

enum ResponseCodes {
	SIGNUP_AND_LOGIN_RESPONSE_CODE = 1,
	LOGIN_RESPONSE_CODE = 3,
	LOGOUT_RESPONSE_CODE,
	GET_ROOMS_RESPONSE_CODE,
	GET_PLAYERS_IN_ROOM_RESPONSE_CODE,
	HIGH_SCORE_RESPONSE_CODE,
	PERSONAL_STATS_RESPONSE_CODE,
	JOIN_ROOM_RESPONSE_CODE,
	CREATE_ROOM_RESPONSE_CODE,
	ERROR_RESPONSE_CODE = 99
};

typedef struct LoginResponse
{
	unsigned int status;
	LoginResponse() : status(SIGNUP_AND_LOGIN_RESPONSE_CODE) {}
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
	SignupResponse() : status(SIGNUP_AND_LOGIN_RESPONSE_CODE) {}
}SignupResponse;

typedef struct ErrorResponse
{
	unsigned int status;
	std::string message;
	ErrorResponse() : message(""), status(ERROR_RESPONSE_CODE) {}
	ErrorResponse(char* msg) : message(msg), status(ERROR_RESPONSE_CODE) {}
	ErrorResponse(std::string msg) : message(msg), status(ERROR_RESPONSE_CODE) {}
}ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
	LogoutResponse() : status(LOGOUT_RESPONSE_CODE){}
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
	std::vector<std::string> statistics;
	getHighScoreResponse() : status(HIGH_SCORE_RESPONSE_CODE) {}
}getHighScoreResponse;

typedef struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
	getPersonalStatsResponse() : status(PERSONAL_STATS_RESPONSE_CODE) {}
}getPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
	JoinRoomResponse() : status(JOIN_ROOM_RESPONSE_CODE) {}
}JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
	CreateRoomResponse() : status(CREATE_ROOM_RESPONSE_CODE) {}
}CreateRoomResponse;