#include "LoginManager.h"
#include "messageException.h"

LoginManager::LoginManager(std::shared_ptr<IDatabase> db) : _database(db)
{
}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	try {
		this->_database->addNewUser(username, password, email);
		this->_loggedUsers.push_back(LoggedUser(username));
	}
	catch (...)
	{
		throw messageException("The user already exist");
	}
}

void LoginManager::login(std::string username, std::string password)
{

	for (auto users: this->_loggedUsers)
	{
		if (users.getUsername() == username)
		{
			throw messageException("The user is already logged in");
		}
	}
	if (this->_database->doesUserExist(username) && this->_database->doesPasswordMatch(username, password))
	{
		this->_loggedUsers.push_back(LoggedUser(username));
	}
	else if(!this->_database->doesUserExist(username))
	{
		throw messageException("User doesn't exist");
	}
	else
	{
		throw messageException("Password doesn't match");
	}
}

void LoginManager::logout(std::string username)
{
	auto obj = std::find(this->_loggedUsers.begin(), this->_loggedUsers.end(), LoggedUser(username));
	if (obj != this->_loggedUsers.end())
	{
		this->_loggedUsers.erase(obj);
	}
}