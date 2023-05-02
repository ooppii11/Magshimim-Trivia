#pragma once
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

#define LOGIN 0
#define SIGNUP 1


class RequestHandlerFactory;


class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);


private:
	LoginManager& _loginManager;
	RequestHandlerFactory& _handlerFactory;

	RequestResult login(RequestInfo requestInfo);
	RequestResult signup(RequestInfo requestInfo);
};