#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : _username(username)
{
}

std::string LoggedUser::getUsername()
{
	return this->_username;
}

bool LoggedUser::operator==(std::string username) 
{
	return this->_username == username;
}
