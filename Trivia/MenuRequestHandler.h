#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "QuizManager.h"
#include "HistoryManager.h"


#define TOP_FIVE 5
#define TWO 2
#define THREE 3
#define FOUR 4

class RequestHandlerFactory;


class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(LoggedUser& user, HistoryManager& historyManager, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory, QuizManager& categoriesManager, LoginManager& loginManager);

	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);
	
private:
	typedef RequestResult(MenuRequestHandler::*function)(RequestInfo);

	LoggedUser _user;
	LoginManager& _loginManager;
	RoomManager&  _roomManager;
	StatisticsManager&  _statisticsManager;
	RequestHandlerFactory&  _handlerFactory;
	HistoryManager& _historyManager;
	QuizManager& _categoriesManager;
	std::map<int, function> _handleRequestFunctions;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);

	RequestResult logout(RequestInfo requestInfo);
	RequestResult getRooms(RequestInfo requestInfo);
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult getPersonalStats(RequestInfo requestInfo);
	RequestResult getHighScore(RequestInfo requestInfo);
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo);
	RequestResult createCategory(RequestInfo requestInfo);
	RequestResult deleteCategory(RequestInfo requestInfo);
	RequestResult addQuestion(RequestInfo requestInfo);
	RequestResult removeQuestion(RequestInfo requestInfo);
	RequestResult getPublicCategories(RequestInfo requestInfo);
	RequestResult getPrivateCategories(RequestInfo requestInfo);
	RequestResult getUserHistory(RequestInfo requestInfo);
	
};