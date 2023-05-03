#pragma once
#include <string>

#define SIGNUP_RESPONSE_CODE 3
#define LOGIN_RESPONSE_CODE 3
#define ERROR_RESPONSE_CODE 99

typedef struct LoginResponse
{
	unsigned int status;
	LoginResponse() : status(LOGIN_RESPONSE_CODE)
	{
	}
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
	SignupResponse() : status(SIGNUP_RESPONSE_CODE)
	{
	}
}SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
	ErrorResponse() : message("")
	{
	}
	ErrorResponse(char* msg) : message(msg)
	{
	}
	ErrorResponse(std::string msg) : message(msg)
	{
	}
}ErrorResponse;
