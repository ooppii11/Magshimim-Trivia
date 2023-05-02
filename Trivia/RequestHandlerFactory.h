#pragma once
#include "IDatabase.h"
<<<<<<< HEAD

=======
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoggedUser.h"
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
<<<<<<< HEAD
	RequestHandlerFactory(IDatabase* datbase);


private:
	IDatabase* _database;
=======
	RequestHandlerFactory(std::shared_ptr<IDatabase> database);

	LoginManager& getLoginManager();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(LoggedUser user);
	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();


private:
	std::shared_ptr<IDatabase> _database;
	LoginManager _loginManager;
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
};