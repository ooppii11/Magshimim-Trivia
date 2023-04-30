#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>

Server::Server():
	_communicator(this->_handlerFactory) {}

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
