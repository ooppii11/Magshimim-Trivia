#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include"GameManager.h"

class RequestHandlerFactory;


class RoomAdminRequestHandler : public IRequestHandler
{
public: 
	RoomAdminRequestHandler(Room& room, LoggedUser user, RoomManager& roomManager, GameManager& gameManager, LoginManager& loginManager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	typedef RequestResult(RoomAdminRequestHandler::* function)(RequestInfo);
	Room& _room;
	LoggedUser _user;
	GameManager& _gameManager;
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	RequestHandlerFactory& _handlerFactory;
	std::map<int, function> _handleRequestFunctions;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);

	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
	RequestResult logout(RequestInfo requestInfo);

};