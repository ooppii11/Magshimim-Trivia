#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"


class RequestHandlerFactory;


class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(Room& room, LoggedUser user, RoomManager& roomManager, LoginManager& loginManager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	typedef RequestResult(RoomMemberRequestHandler::* function)(RequestInfo);
	Room& _room;
	LoggedUser _user;
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	RequestHandlerFactory&  _handlerFactory;
	std::map<int, function> _handleRequestFunctions;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);
	RequestResult leaveRoom(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);

	RequestResult logout(RequestInfo requestInfo);
};