#include "LoginManager.h"

LoginManager::LoginManager(const std::shared_ptr<IDatabase>& db) : _database(db)
{
}

void LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	this->_database->addNewUser(username, password, email);
	this->_loggedUsers.push_back(LoggedUser(username));
}

void LoginManager::login(const std::string& username, const std::string& password)
{
	if (this->_database->doesUserExist(username) && this->_database->doesPasswordMatch(username, password))
	{
		this->_loggedUsers.push_back(LoggedUser(username));
	}
	else { throw std::exception("Passwrord not match"); }
}

void LoginManager::logout(const std::string& username)
{
	auto obj = std::find(this->_loggedUsers.begin(), this->_loggedUsers.end(), LoggedUser(username));
	if (obj != this->_loggedUsers.end())
	{
		this->_loggedUsers.erase(obj);
	}
}