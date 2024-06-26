#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "QuizManager.h"
#include "StatisticsManager.h"
#include "HistoryManager.h"
#include "QuizManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameManager.h"
#include "Game.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(std::shared_ptr<IDatabase> database);

	LoginManager& getLoginManager();
	std::shared_ptr<MenuRequestHandler> createMenuRequestHandler(LoggedUser user);
	std::shared_ptr<LoginRequestHandler> createLoginRequestHandler();
	StatisticsManager&  getStatisticsManager();
	RoomManager&  getRoomManager();
	std::shared_ptr<RoomAdminRequestHandler> createRoomAdminRequestHandler(LoggedUser, Room&);
	std::shared_ptr<RoomMemberRequestHandler> createRoomMemberRequestHandler(LoggedUser, Room&);
	std::shared_ptr<GameRequestHandler> createGameRequestHandler(LoggedUser user, unsigned int gameId);
	GameManager& getGameManager();

private:
	std::shared_ptr<IDatabase> _database;
	LoginManager _loginManager;
	RoomManager _roomManager;	
	StatisticsManager _statisticsManager;
	QuizManager _quizManager;
	HistoryManager _historyManager;

	GameManager _gameManager;
};