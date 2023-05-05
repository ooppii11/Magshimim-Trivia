#pragma once
#include <string>

#define SIGNUP_REQUEST_CODE 1
#define LOGIN_REQUEST_CODE 2

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