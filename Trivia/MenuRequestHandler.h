#pragma once
#include "IRequestHandler.h"


class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);
};