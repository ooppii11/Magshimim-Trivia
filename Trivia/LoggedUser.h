#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	bool operator==(const LoggedUser& user);
private:
	std::string _username;
};