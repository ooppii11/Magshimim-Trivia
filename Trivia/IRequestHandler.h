#pragma once
#include <vector>
#include <ctime>

typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
	std::vector<char> buffer;
} RequestInfo;

typedef struct RequestResult
{
	std::vector<char> response;
	struct IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo) = 0;
};