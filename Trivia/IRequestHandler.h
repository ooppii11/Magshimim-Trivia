#pragma once
<<<<<<< HEAD
#include <vector>
#include <ctime>

=======
#include <memory>
#include <vector>
#include <ctime>
#include "BufferDeserializer.hpp"


class IRequestHandler;


>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
typedef struct RequestInfo
{
	int id;
	time_t receivalTime;
<<<<<<< HEAD
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
=======
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
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
