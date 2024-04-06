#pragma once
#include <memory>
#include <vector>
#include <ctime>
#include "BufferDeserializer.hpp"


class IRequestHandler;


typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	Buffer buffer;
} RequestInfo;


typedef struct RequestResult
{
	Buffer response;
	std::shared_ptr<IRequestHandler> newHandler;
} RequestResult;


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};
