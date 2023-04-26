#pragma once
#include "RequestHandlerFactory.h"
#include "Communicator.h"


#define EXIT_MESSAGE "EXIT"


class Server
{
public:
	Server();
	~Server();
	void run(int port);

private:
	Communicator _communicator;
	RequestHandlerFactory _handlerFactory;
};

