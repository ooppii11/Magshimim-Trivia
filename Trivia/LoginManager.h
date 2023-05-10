#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <memory>
#include <vector>
#include <algorithm>

class LoginManager 
{
public:
	LoginManager(const std::shared_ptr<IDatabase>& db);

	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
private:
	std::shared_ptr<IDatabase> _database;
	std::vector<LoggedUser> _loggedUsers;
};