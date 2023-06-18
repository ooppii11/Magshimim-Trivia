#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "messageException.h"
#include "IDatabase.h"
#include "Request.h"
#include "Response.h"


GameRequestHandler::GameRequestHandler(LoggedUser user, unsigned int gameId, GameManager& gameManager, RoomManager& roomManager,  HistoryManager& historyManager, LoginManager& loginManager, RequestHandlerFactory& handlerFacroty) :
	_user(user), _roomManager(roomManager), _gameManager(gameManager), _handlerFactory(handlerFacroty), _game(gameManager.getGameById(gameId)), _loginManager(loginManager), _historyManager(historyManager)
{
	this->_handleRequestFunctions[LOGOUT_REQUEST_CODE] = &GameRequestHandler::logout;
	this->_handleRequestFunctions[LEAVE_GAME_REQUEST_CODE] = &GameRequestHandler::leaveGame;
	this->_handleRequestFunctions[GET_QUESTION_REQUEST_CODE] = &GameRequestHandler::getQuestion;
	this->_handleRequestFunctions[SUBMIT_ANSWER_REQUEST_CODE] = &GameRequestHandler::submitAnswer;
	this->_handleRequestFunctions[GET_GAME_RESULTS_REQUEST_CODE] = &GameRequestHandler::getGameResults;
}

bool GameRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return  LEAVE_GAME_REQUEST_CODE == requestInfo.id ||
		GET_QUESTION_REQUEST_CODE == requestInfo.id ||
		SUBMIT_ANSWER_REQUEST_CODE == requestInfo.id ||
		GET_GAME_RESULTS_REQUEST_CODE == requestInfo.id;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
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


RequestResult GameRequestHandler::wrapperHandleRequest(function function, RequestInfo requestInfo)
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
	catch (std::exception& e)
	{
		result.response = Serializer::serializeResponse(ErrorResponse(e.what()));
		result.newHandler = std::shared_ptr<MenuRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	}
	return result;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo)
{
	RequestResult result;
	GetQuestionResponse response;
	Question question = this->_game.getQuestionForUser(this->_user);

	response.question = question.getQuestion();
	response.answers = question.getPossibleAnswers();

	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createGameRequestHandler(this->_user, this->_game.getGameId()));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	RequestResult result;
	SubmitAnswerRequest request;
	SubmitAnswerResponse response;

	request = Deserializer::deserializeSubminAnswerRequest(requestInfo.buffer);
	
	response.correctAnswerIndex = this->_game.submitAnswer(this->_user, request.answerIndex);

	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createGameRequestHandler(this->_user, this->_game.getGameId()));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo)
{
	RequestResult result;
	GetGameResultsResponse response;

	std::vector<PlayerResults> gameResults = this->_game.getPalyersResults();
	int rank = 0;
	for(rank = 0; rank < gameResults.size(); rank ++)
	{
		if (gameResults[rank].username == this->_user.getUsername())
		{
			this->updateUserHistoryAndStatistics(rank + 1, gameResults[rank]);

		}
	}

	response.results = gameResults;
	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(response);

	this->_game.removePlayer(this->_user);
	if (this->_game.getNumberOfPslyers() == 0)
	{
		this->_gameManager.deleteGame(this->_game.getGameId());
		this->_roomManager.deleteRoom(this->_game.getGameId());
	}

	return result;
}

RequestResult GameRequestHandler::logout(RequestInfo requestInfo)
{
	if (this->_game.getNumberOfPslyers() == 0)
	{
		this->_gameManager.deleteGame(this->_game.getGameId());
		this->_roomManager.deleteRoom(this->_game.getGameId());
	}
	this->_loginManager.logout(this->_user.getUsername());
	return RequestResult();
}

void GameRequestHandler::updateUserHistoryAndStatistics(int rank, PlayerResults userResult)
{
	History userHistory;

	RoomData roomData = this->_roomManager.getRoom(this->_game.getGameId()).getRoomData();

	userHistory.answers = userResult.correctAnswerCount + userResult.wrongAnswerCount;
	userHistory.avergeTime = userResult.averageAnswerTime;
	userHistory.correctAnswers = userResult.correctAnswerCount;
	userHistory.categoryId = roomData.categorieId;
	userHistory.rank = rank;

	this->_historyManager.addNewHistory(this->_user.getUsername(), userHistory);
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
	RequestResult result;
	
	this->_game.removePlayer(this->_user);
	if (this->_game.getNumberOfPslyers() == 0)
	{
		this->_gameManager.deleteGame(this->_game.getGameId());
		this->_roomManager.deleteRoom(this->_game.getGameId());
	}
	
	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(LeaveGameResponse());

	return result;
}

