#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "messageException.h"
#include "IDatabase.h"
#include "Request.h"
#include "Response.h"

/*
GameRequestHandler::GameRequestHandler(LoggedUser user, Game& game, GameManager& gameManager, RequestHandlerFactory& handlerFacroty) :
	_user(user), _game(game), _gameManager(gameManager), _handlerFactory(handlerFacroty) {}

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
	catch (...)
	{
		result.response = Serializer::serializeResponse(ErrorResponse());
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

	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createGameRequestHandler(this->_user, this->_game));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo)
{
	RequestResult result;
	SubmitAnswerRequest request;
	SubmitAnswerResponse response;

	request = Deserializer::deserializeSubminAnswerRequest(requestInfo.buffer);
	
	this->_game.submitAnswer(this->_user, request.answerIndex);
	response.correctAnswerIndex = this->_game.getQuestionForUser(this->_user).getCorrectAnswerId();

	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createGameRequestHandler(this->_user, this->_game));
	result.response = Serializer::serializeResponse(response);

	return result;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo)
{
	RequestResult result;
	
	this->_game.removePlayer(this->_user);
	
	result.newHandler = std::shared_ptr<IRequestHandler>(this->_handlerFactory.createMenuRequestHandler(this->_user));
	result.response = Serializer::serializeResponse(LeaveGameResponse());

	return result;
}
*/
