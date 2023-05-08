#include "LoggedUser.h"

LoggedUser::LoggedUser(std::string username) : _username(username)
{
}

std::string LoggedUser::getUsername()
{
	return this->_username;
}

bool LoggedUser::operator==(const LoggedUser& user)
{
	return  this->_username == user._username;
}
