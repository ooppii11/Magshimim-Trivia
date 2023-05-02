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
<<<<<<< HEAD
	IDatabase* _database;
=======
	std::shared_ptr<IDatabase> _database;
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
	RequestHandlerFactory _handlerFactory;
};

