#include "MenuRequestHandler.h"

#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "messageException.h"
#include "Request.h"
#include "Response.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) :
	_user(user), _roomManager(roomManager), _statisticsManager(statisticsManager), _handlerFactory(handlerFactory)
{
	this->_handleRequestFunctions[LOGOUT_REQUEST_CODE] = &MenuRequestHandler::signout;
	this->_handleRequestFunctions[GET_ROOMS_REQUEST_CODE] = &MenuRequestHandler::getRooms;
	this->_handleRequestFunctions[GET_PLAYERS_IN_ROOM_REQUEST_CODE] = &MenuRequestHandler::getPlayersInRoom;
	this->_handleRequestFunctions[HIGH_SCORE_REQUEST_CODE] = &MenuRequestHandler::getHighScore;
	this->_handleRequestFunctions[PERSONAL_STATS_REQUEST_CODE] = &MenuRequestHandler::getPersonalStats;
	this->_handleRequestFunctions[JOIN_ROOM_REQUEST_CODE] = &MenuRequestHandler::joinRoom;
	this->_handleRequestFunctions[CREATE_ROOM_REQUEST_CODE] = &MenuRequestHandler::createRoom;
	this->_handleRequestFunctions[ADD_CATEGORIE_REQUEST_CODE] = &MenuRequestHandler::createCategory;
	this->_handleRequestFunctions[REMOVE_CATEGORIE_REQUEST_CODE] = &MenuRequestHandler::deleteCategory;
	this->_handleRequestFunctions[ADD_QUESTION_REQUEST_CODE] = &MenuRequestHandler::addQuestion;
	this->_handleRequestFunctions[REMOVE_QUESTION_REQUEST_CODE] = &MenuRequestHandler::removeQuestion;
}


bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return LOGOUT_REQUEST_CODE == requestInfo.id ||
		GET_ROOMS_REQUEST_CODE == requestInfo.id ||
		GET_PLAYERS_IN_ROOM_REQUEST_CODE == requestInfo.id ||
		HIGH_SCORE_REQUEST_CODE == requestInfo.id ||
		PERSONAL_STATS_REQUEST_CODE == requestInfo.id ||
		JOIN_ROOM_REQUEST_CODE == requestInfo.id ||
		CREATE_ROOM_REQUEST_CODE == requestInfo.id ||
		ADD_CATEGORIE_REQUEST_CODE == requestInfo.id ||
		REMOVE_CATEGORIE_REQUEST_CODE == requestInfo.id ||
		ADD_QUESTION_REQUEST_CODE == requestInfo.id ||
		REMOVE_QUESTION_REQUEST_CODE == requestInfo.id;
}


RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult result;
	std::map<int, function>::iterator it;

	it = this->_handleRequestFunctions.find(requestInfo.id);
	if (it != this->_handleRequestFunctions.end())
	{
		result = (this->*(it->second))(requestInfo);
	}
	return result;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo)
{
	RequestResult result;

	result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	result.response = Serializer::serializeResponse(LogoutResponse());
	
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
	RequestResult result;
	GetRoomsResponse response;
	
	response.rooms = this->_roomManager.getRooms();
	response.status = GET_ROOMS_RESPONSE_CODE;
	result.newHandler = std::shared_ptr<IRequestHandler>(this);
	result.response = Serializer::serializeResponse(response);
	
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{
	GetPlayersInRoomRequest request;
	RequestResult result;
	GetPlayersInRoomResponse response;
	Room room;
	try
	{
		request = Deserializer::deserializeGetPlayersRequest(requestInfo.buffer);
		room = this->_roomManager.getRoom(request.roomId);
		response.rooms = room.getAllUsers();
		response.status = GET_PLAYERS_IN_ROOM_RESPONSE_CODE;

		result.newHandler = std::shared_ptr<IRequestHandler>(this);
		result.response = Serializer::serializeResponse(response);
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo requestInfo)
{
	RequestResult result;
	getPersonalStatsResponse response;
	try
	{
		response.statistics = this->_statisticsManager.getUserStatistics(this->_user.getUsername());
		response.status = PERSONAL_STATS_RESPONSE_CODE;

		result.newHandler = std::shared_ptr<IRequestHandler>(this);
		result.response = Serializer::serializeResponse(response);
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo requestInfo)
{
	RequestResult result;
	getHighScoreResponse response;
	try
	{
		response.statistics = this->_statisticsManager.getHighScore(TOP_FIVE);
		response.status = HIGH_SCORE_RESPONSE_CODE;

		result.newHandler = std::shared_ptr<IRequestHandler>(this);
		result.response = Serializer::serializeResponse(response);
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
	JoinRoomRequest request;
	RequestResult result;	
	
	try
	{
		request = Deserializer::deserializeJoinRoomRequest(requestInfo.buffer);
		this->_roomManager.getRoom(request.roomId).addUser(this->_user);
		result.newHandler = std::shared_ptr<IRequestHandler>(this);
		result.response = Serializer::serializeResponse(JoinRoomResponse());
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<IRequestHandler>(nullptr);
	}
	return result;
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::createCategory(RequestInfo requestInfo) 
{
	return RequestResult();
}

RequestResult MenuRequestHandler::deleteCategory(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo requestInfo)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::removeQuestion(RequestInfo requestInfo)
{
	return RequestResult();
}