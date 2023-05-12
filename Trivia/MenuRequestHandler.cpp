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
