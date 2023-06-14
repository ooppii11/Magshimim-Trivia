#include "RoomAdminRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "Request.h"
#include "Response.h"
#include "messageException.h"


RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, LoginManager& loginManager, RequestHandlerFactory& handlerFactory) :
	_room(room), _user(user), _roomManager(roomManager), _handlerFactory(handlerFactory), _loginManager(loginManager)
{
	this->_handleRequestFunctions[CLOSE_ROOM_REQUEST_CODE] = &RoomAdminRequestHandler::closeRoom;
	this->_handleRequestFunctions[START_GAME_REQUEST_CODE] = &RoomAdminRequestHandler::startGame;
	this->_handleRequestFunctions[GET_ROOM_STATE_REQUEST_CODE] = &RoomAdminRequestHandler::getRoomState;
}


bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) 
{
	return CLOSE_ROOM_REQUEST_CODE == requestInfo.id || START_GAME_REQUEST_CODE == requestInfo.id || GET_ROOM_STATE_REQUEST_CODE == requestInfo.id;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
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

RequestResult RoomAdminRequestHandler::wrapperHandleRequest(function function, RequestInfo requestInfo)
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

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
	RequestResult result;
	CloseRoomResponse response;

	this->_roomManager.deleteRoom(this->_room.getRoomData().id);
	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{
	RequestResult result;
	CloseRoomResponse response;
	RoomData roomData = this->_room.getRoomData();

	roomData.isActive = true;
	this->_room.setRoomData(roomData);

	result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo)
{
	RequestResult result;
	GetRoomStateResponse response;
	RoomData roomData = this->_room.getRoomData();

	response.status = GET_ROOM_STATE_RESPONSE_CODE;
	//response.status = this->_roomManager.getRoomState(roomData.id);
	response.players = this->_room.getAllUsers();
	response.hasGameBegun = roomData.isActive;
	response.answerTimeout = roomData.timePerQuestion;
	response.questionCount = roomData.numOfQuestionsInGame;

	result.newHandler = std::shared_ptr<RoomAdminRequestHandler>(this->_handlerFactory.createRoomAdminRequestHandler(this->_user, this->_room));
	result.response = Serializer::serializeResponse(response);

	return result;
}

void RoomAdminRequestHandler::logout(RequestInfo requestInfo)
{
	this->_loginManager.logout(this->_user.getUsername());
}