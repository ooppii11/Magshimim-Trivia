#pragma once
#include <string>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include <map>
#include <WinSock2.h>
#include <Windows.h>


#define MIN_PORT 1024
#define MAX_PORT 65525
#define START_MESSAGE "Hello"


class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequests(int port);
		

private:
	std::map<SOCKET, IRequestHandler* > _clients;
	SOCKET _serverSocket;
	RequestHandlerFactory& _handlerFactory;

	void bindAndListen(int port);
	void acceptNewClient();
	void handleNewClient(SOCKET client);

	bool validPort(int port);
	std::string recvMessage(SOCKET sock, int size);
};