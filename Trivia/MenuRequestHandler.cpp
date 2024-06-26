#include "MenuRequestHandler.h"
#include "MenuRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "messageException.h"
#include "IDatabase.h"
#include "Request.h"
#include "Response.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, HistoryManager& historyManager, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory, QuizManager& categoriesManager, LoginManager& loginManager):
	_user(user), _historyManager(historyManager), _roomManager(roomManager), _statisticsManager(statisticsManager), _handlerFactory(handlerFactory), _categoriesManager(categoriesManager), _loginManager(loginManager)
{
	this->_handleRequestFunctions[GET_USER_HISTORY_REQUEST_CODE] = &MenuRequestHandler::getUserHistory;
	this->_handleRequestFunctions[LOGOUT_REQUEST_CODE] = &MenuRequestHandler::logout;
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
	this->_handleRequestFunctions[GET_PRIVATE_CATEGORIES_REQUEST_CODE] = &MenuRequestHandler::getPrivateCategories;
	this->_handleRequestFunctions[GET_PUBLIC_CATEGORIES_REQUEST_CODE] = &MenuRequestHandler::getPublicCategories;
}


bool MenuRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return GET_USER_HISTORY_REQUEST_CODE == requestInfo.id || 
		LOGOUT_REQUEST_CODE == requestInfo.id ||
		GET_ROOMS_REQUEST_CODE == requestInfo.id ||
		GET_PLAYERS_IN_ROOM_REQUEST_CODE == requestInfo.id ||
		HIGH_SCORE_REQUEST_CODE == requestInfo.id ||
		PERSONAL_STATS_REQUEST_CODE == requestInfo.id ||
		GET_PUBLIC_CATEGORIES_RESPONSE_CODE == requestInfo.id ||
		GET_PRIVATE_CATEGORIES_RESPONSE_CODE == requestInfo.id ||
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
		result = wrapperHandleRequest(it->second, requestInfo);
	}
	return result;
}

RequestResult MenuRequestHandler::wrapperHandleRequest(function function, RequestInfo requestInfo)
{
	RequestResult result;
	try
	{
		result = (this->*(function))(requestInfo);
	}
	catch (messageException& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	}
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
		result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	}
	return result;
}

RequestResult MenuRequestHandler::logout(RequestInfo requestInfo)
{
	RequestResult result;
	this->_loginManager.logout(this->_user.getUsername());
	result.newHandler = std::shared_ptr<MenuRequestHandler>(nullptr);
	result.response = Serializer::serializeResponse(LogoutResponse());
	
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
	RequestResult result;
	GetRoomsResponse response;
	
	response.rooms = this->_roomManager.getRooms();
	response.status = GET_ROOMS_RESPONSE_CODE;
	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);
	
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{
	GetPlayersInRoomRequest request;
	RequestResult result;
	GetPlayersInRoomResponse response;
	Room room;

	request = Deserializer::deserializeGetPlayersRequest(requestInfo.buffer);
	room = this->_roomManager.getRoom(request.roomId);
	response.rooms = room.getAllUsers();
	response.status = GET_PLAYERS_IN_ROOM_RESPONSE_CODE;
	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);
	
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo requestInfo)
{
	RequestResult result;
	getPersonalStatsResponse response;

	response.statistics = this->_statisticsManager.getUserStatistics(this->_user.getUsername());
	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);
	
	return result;
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo requestInfo)
{
	RequestResult result;
	getHighScoreResponse response;
	
	response.statistics = this->_statisticsManager.getHighScore(TOP_FIVE);
	response.status = HIGH_SCORE_RESPONSE_CODE;
	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);
	
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
	JoinRoomRequest request;
	RequestResult result;	

	request = Deserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	if (this->_roomManager.getRoomState(request.roomId) == true)
	{
		throw messageException("Room is already active");
	}
	this->_roomManager.getRoom(request.roomId).addUser(this->_user);
	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createRoomMemberRequestHandler(this->_user, this->_roomManager.getRoom(request.roomId)));
	result.response = Serializer::serializeResponse(JoinRoomResponse());
	
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo)
{
	RequestResult result;
	CreateRoomRequest request;
	RoomData roomData;
	CreateRoomResponse response;
	Room room;

	request = Deserializer::deserializeCreateRoomRequest(requestInfo.buffer);
	roomData.categorieId = request.categorieId;
	roomData.maxPlayers = request.maxUsers;
	roomData.name = request.roomName;
	roomData.numOfQuestionsInGame= request.questionCount;
	roomData.timePerQuestion = request.answerTimeout;
	roomData.isActive = false;

	response.roomId  = this->_roomManager.createRoom(this->_user, roomData);
	response.status = false;
	
	result.newHandler = std::shared_ptr<RoomAdminRequestHandler>(this->_handlerFactory.createRoomAdminRequestHandler(this->_user, this->_roomManager.getRoom(response.roomId)));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult MenuRequestHandler::createCategory(RequestInfo requestInfo) 
{
	RequestResult result;
	AddCategorieRequest request;
	Category category;
	
	request = Deserializer::addCategorieToUser(requestInfo.buffer);

	category.categoryName = request.categoryName;
	category.permission = request.permission;
	this->_categoriesManager.addNewCategory(category, this->_user.getUsername());

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(CreateRoomResponse());

	return result;
}

RequestResult MenuRequestHandler::deleteCategory(RequestInfo requestInfo)
{
	RequestResult result;
	RemoveCategorieRequest request;

	request = Deserializer::removeCategorieFromUser(requestInfo.buffer);
	this->_categoriesManager.deleteCategory(request.categorieId, this->_user.getUsername());

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(RemoveCategorieResponse());

	return result;
}

RequestResult MenuRequestHandler::addQuestion(RequestInfo requestInfo)
{
	RequestResult result;
	AddQuestionRequest request;
	QuestionStruct question;

	request = Deserializer::addQuestionToUserCategorie(requestInfo.buffer);
	if (request.answers.size() != FOUR) { throw messageException("Answers are missing"); }
	if (request.correctAnswerIndex < 0 || request.correctAnswerIndex >= FOUR) { messageException("Unvalid Index"); }

	question.question = request.questionName;
	question.correctAnswerIndex = request.correctAnswerIndex;
	question.firstAnswer = request.answers[0];
	question.secondAnswer = request.answers[1];
	question.thirdAnswer = request.answers[TWO];
	question.fourthAnswer = request.answers[THREE];

	this->_categoriesManager.addNewQuestion(request.categorieId, this->_user.getUsername(), question);

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(AddQuestionResponse());

	return result;
}

RequestResult MenuRequestHandler::removeQuestion(RequestInfo requestInfo)
{
	RequestResult result;
	RemoveQuestionRequest request;

	request = Deserializer::removeQuestionFromUserCategorie(requestInfo.buffer);
	this->_categoriesManager.deleteQuestion(request.categorieId, this->_user.getUsername(), request.questionName);

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(RemoveQuestionResponse());

	return result;
}

RequestResult MenuRequestHandler::getPublicCategories(RequestInfo requestInfo)
{
	RequestResult result;
	getPublicCategoriesResponse reponse;

	reponse.status = GET_PUBLIC_CATEGORIES_RESPONSE_CODE;
	reponse.publicCategories = this->_categoriesManager.getPublicCategories();

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(reponse);

	return result;
}

RequestResult MenuRequestHandler::getPrivateCategories(RequestInfo requestInfo)
{
	RequestResult result;
	getPrivateCategoriesResponse reponse;

	reponse.status = GET_PRIVATE_CATEGORIES_RESPONSE_CODE;
	reponse.PrivateCategories = this->_categoriesManager.getPrivagteCategories(this->_user.getUsername());

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(reponse);

	return result;
}

RequestResult MenuRequestHandler::getUserHistory(RequestInfo requestInfo)
{
	RequestResult result;
	struct getUserHistory reponse;

	reponse.history = this->_historyManager.getUserLastFiveHistory(this->_user.getUsername());

	result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(reponse);

	return result;
}
