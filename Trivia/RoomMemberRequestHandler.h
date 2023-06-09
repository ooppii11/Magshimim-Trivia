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
	RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(RequestInfo requestInfo) const;
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	typedef RequestResult(RoomMemberRequestHandler::* function)(RequestInfo);
	Room _room;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory&  _handlerFactory;
	std::map<int, function> _handleRequestFunctions;

	RequestResult wrapperHandleRequest(function function, RequestInfo requestInfo);
	RequestResult leaveRoom(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};