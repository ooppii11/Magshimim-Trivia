#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include "SqliteDatabase.h"

Server::Server():
<<<<<<< HEAD
	_database(new SqliteDatabase()), _handlerFactory(this->_database), _communicator(this->_handlerFactory) {}

=======
	_database(std::shared_ptr<IDatabase>(new SqliteDatabase())), _handlerFactory(_database), _communicator(this->_handlerFactory) {}
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
Server::~Server() {}

void Server::run(int port)
{
	std::string message = "";

	std::thread tr(&Communicator::startHandleRequests, this->_communicator, port);
	tr.detach();

	while (true)
	{
		std::cin >> message;
		if (message == EXIT_MESSAGE) { return; }
	}
}
