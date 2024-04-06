#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

#include "GameManager.h"
#include "Game.h"


class RequestHandlerFactory;


class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser user, unsigned int gameId, GameManager& _gameManager, RoomManager& roomManager, HistoryManager& _historyManager, LoginManager& loginManager, RequestHandlerFactory& handlerFacroty);
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	typedef RequestResult(GameRequestHandler::* function)(RequestInfo);
	Game& _game;
	LoggedUser _user;
	GameManager& _gameManager;
	RequestHandlerFactory& _handlerFactory;
	HistoryManager& _historyManager;
	std::map<int, function> _handleRequestFunctions;
	LoginManager& _loginManager;
	RoomManager& _roomManager;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);

	RequestResult getQuestion(RequestInfo requestInfo);
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults(RequestInfo requestInfo);
	RequestResult leaveGame(RequestInfo requestInfo);

	RequestResult logout(RequestInfo requestInfo);

	void updateUserHistoryAndStatistics(int rank, PlayerResults userResult);

};