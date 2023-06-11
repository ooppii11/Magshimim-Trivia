#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"


class RequestHandlerFactory;


class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(LoggedUser user, Game& _game, GameManager& _gameManager, RequestHandlerFactory& handlerFacroty);
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	Game& _game;
	LoggedUser _user;
	GameManager& _gameManager;
	RequestHandlerFactory& _handlerFacroty;


	RequestResult getQuestion(RequestInfo);
	RequestResult submitAnswer(RequestInfo);
	RequestResult getGameResults(RequestInfo);
	RequestResult leaveGame(RequestInfo);
}