#pragma once
#include "IDatabase.h"
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
	std::shared_ptr<IDatabase> _database;
	RequestHandlerFactory _handlerFactory;
};

