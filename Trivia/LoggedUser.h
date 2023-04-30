#pragma once
#include <string>
class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	bool operator==(std::string username);
private:
	std::string _username;
};