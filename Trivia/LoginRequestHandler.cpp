#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.h"
#include "Request.h"
#include "Response.h"


LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) :
    _loginManager(loginManager), _handlerFactory(handlerFactory) {}

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
    return LOGIN == requestInfo.id || SIGNUP == requestInfo.id;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
    RequestResult result;
    if (LOGIN == requestInfo.id) { result = this->login(requestInfo); }
    else if (SIGNUP == requestInfo.id) { result = this->signup(requestInfo); }

    return result;
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
    RequestResult result;
    try
    {
       LoginRequest request = Deserializer::deserializeLoginRequest(requestInfo.buffer);
       this->_loginManager.login(request.username, request.password);
        LoggedUser user(request.username);
        result.newHandler = this->_handlerFactory.createMenuRequestHandler(user);
        result.response = Serializer::serializeResponse(LoginResponse());
    }
    catch (...)
    {
        result.response = Serializer::serializeResponse(ErrorResponse());
        result.newHandler = std::shared_ptr<LoginRequestHandler> (nullptr);
    }
    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo requestInfo)
{
    RequestResult result;
    try
    {
        SignupRequest request = Deserializer::deserializeSignupRequest(requestInfo.buffer);
        this->_loginManager.signup(request.username, request.password, request.email);
        LoggedUser user(request.username);
        result.newHandler = this->_handlerFactory.createMenuRequestHandler(user);
        result.response = Serializer::serializeResponse(LoginResponse());
    }
    catch (...)
    {
        result.response = Serializer::serializeResponse(ErrorResponse());
        result.newHandler = std::shared_ptr<LoginRequestHandler>(nullptr);
    }
    return result;
}
