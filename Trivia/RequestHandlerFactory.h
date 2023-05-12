#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;


class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase> database);

	LoginManager& getLoginManager();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(LoggedUser user);
	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	StatisticsManager&  getStatisticsManager() const;
	RoomManager&  getRoomManager() const;



private:
	std::shared_ptr<IDatabase> _database;
	LoginManager _loginManager;
	RoomManager _roomManager;	
	StatisticsManager _statisticsManager;

};