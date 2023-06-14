#include "RoomMemberRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "Request.h"
#include "Response.h"
#include "messageException.h"
#include "IDatabase.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, LoggedUser user, RoomManager& roomManager, LoginManager& loginManager, RequestHandlerFactory& handlerFactory):
	_room(room), _user(user), _roomManager(roomManager), _handlerFactory(handlerFactory), _loginManager(loginManager)
{
	this->_handleRequestFunctions[LOGOUT_REQUEST_CODE] = &RoomMemberRequestHandler::logout;
	this->_handleRequestFunctions[LEAVE_ROOM_REQUEST_CODE] = &RoomMemberRequestHandler::leaveRoom;
	this->_handleRequestFunctions[GET_ROOM_STATE_REQUEST_CODE] = &RoomMemberRequestHandler::getRoomState;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return GET_ROOM_STATE_REQUEST_CODE == requestInfo.id || LEAVE_ROOM_REQUEST_CODE == requestInfo.id;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	std::map<int, function>::iterator it;

	it = this->_handleRequestFunctions.find(requestInfo.id);
	if (it != this->_handleRequestFunctions.end())
	{
		result = wrapperHandleRequest(it->second, requestInfo);
	}
	return result;
}

RequestResult RoomMemberRequestHandler::wrapperHandleRequest(function function, RequestInfo requestInfo)
{
	RequestResult result;
	try
	{
		result = (this->*(function))(requestInfo);
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	}
	return result;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	RequestResult result;
	LeaveRoomResponse response;

	this->_room.removeUser(this->_user);

	result.newHandler = std::shared_ptr<RoomMemberRequestHandler> (this->_handlerFactory.createRoomMemberRequestHandler(this->_user, this->_room));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;
	try
	{
		GetRoomStateResponse response;
		RoomData roomData = this->_room.getRoomData();
		response.status = GET_PLAYERS_IN_ROOM_RESPONSE_CODE;
		response.players = this->_room.getAllUsers();
		response.hasGameBegun = roomData.isActive;
		response.answerTimeout = roomData.timePerQuestion;
		response.questionCount = roomData.numOfQuestionsInGame;

		result.newHandler = std::shared_ptr<RoomMemberRequestHandler>(this->_handlerFactory.createRoomMemberRequestHandler(this->_user, this->_room));
		result.response = Serializer::serializeResponse(response);
	}
	catch (...) 
	{
		result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
		result.response = Serializer::serializeResponse(ErrorResponse("Room is close"));
	}
	
	
	return result;
}

RequestResult RoomMemberRequestHandler::logout(RequestInfo requestInfo)
{
	this->_loginManager.logout(this->_user.getUsername());
	this->_room.removeUser(this->_user);
	return RequestResult();
}