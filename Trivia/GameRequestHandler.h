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
	GameRequestHandler(LoggedUser user, unsigned int gameId, GameManager& _gameManager, RequestHandlerFactory& handlerFacroty);
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	typedef RequestResult(GameRequestHandler::* function)(RequestInfo);
	Game& _game;
	LoggedUser _user;
	GameManager& _gameManager;
	RequestHandlerFactory& _handlerFactory;
	std::map<int, function> _handleRequestFunctions;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);

	RequestResult getQuestion(RequestInfo requestInfo);
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults(RequestInfo requestInfo);
	RequestResult leaveGame(RequestInfo requestInfo);
};