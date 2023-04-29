#pragma once
#include <string>
typedef struct LoginResponse
{
	unsigned int status;
	LoginResponse() : status(3)
	{
	}
}LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
	SignupResponse() : status(3)
	{
	}
}SignupResponse;

typedef struct ErrorResponse
{
	std::string message;
}ErrorResponse;
