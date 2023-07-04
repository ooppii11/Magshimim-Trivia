#pragma once
#include <string>
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include <map>
#include <mutex>
#include <WinSock2.h>
#include <Windows.h>
#include "BufferDeserializer.hpp"
#include "IRequestHandler.h"
#include "CryptoManager.h"


#define MIN_PORT 1024
#define MAX_PORT 65525
#define START_MESSAGE "Hello"


#define MESSAGE_HEADR_SIZE 5


class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequests(int port);
		

private:
	std::map<SOCKET, std::shared_ptr<IRequestHandler>> _clients;
	SOCKET _serverSocket;
	RequestHandlerFactory& _handlerFactory;
	std::mutex _handlerFactoryMutex;

	void bindAndListen(int port);
	void acceptNewClient();
	void handleNewClient(SOCKET client);

	bool validPort(int port);
	RequestInfo recvMessage(SOCKET sock);
	void sendMessage(SOCKET sock, Buffer response);
};