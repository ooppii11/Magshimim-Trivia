#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <memory>
#include <vector>
#include <algorithm>

class LoginManager 
{
public:
	LoginManager(std::shared_ptr<IDatabase> db);

	void signup(std::string username, std::string password, std::string email);
	void login(std::string username, std::string password);
	void logout(std::string username);
private:
	std::shared_ptr<IDatabase> _database;
	std::vector<LoggedUser> _loggedUsers;
};