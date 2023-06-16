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
/*
bool LoggedUser::operator<(const LoggedUser& user)
{
	return this->_username < user._username;
}*/
/*
bool LoggedUser::operator()(const LoggedUser& user1, const LoggedUser& user2) const
{
	return user1._username < user2._username;
}*/
