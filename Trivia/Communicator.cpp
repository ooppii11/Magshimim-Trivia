#include "Communicator.h"
#include <iostream>
#include <thread>
#include "Request.h"
#include "JsonRequestPacketSerializer.hpp"
#include "Response.h"

Communicator::Communicator(RequestHandlerFactory& handlerFactory):
	_handlerFactory(handlerFactory)
{
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		closesocket(this->_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests(int port)
{
	if (!this->validPort(port))
	{
		throw std::exception("Unvalid port");
	}
	this->bindAndListen(port);
}

void Communicator::bindAndListen(int port)
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}
	// Start listening for incoming requests of clients
	if (listen(this->_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		
		std::cout << "Waiting for client connection request" << std::endl;
		this->acceptNewClient();
	}
}


void Communicator::acceptNewClient()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__" - accept");
	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	this->_clients[client_socket] = this->_handlerFactory.createLoginRequestHandler();
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	RequestInfo clientRequest = { 0 };
	RequestResult response = { 0 };

	try
	{
		while (this->_clients[clientSocket].get() != nullptr)
		{
			//std::lock_guard<std::mutex> mutex(this->_handlerFactoryMutex);
			clientRequest = this->recvMessage(clientSocket);
			if (this->_clients[clientSocket].get()->isRequestRelevant(clientRequest))
			{
				std::unique_lock<std::mutex> messagesLock(this->_handlerFactoryMutex);

				response = this->_clients[clientSocket].get()->handleRequest(clientRequest);
				this->_clients[clientSocket] = response.newHandler;
				messagesLock.unlock();

			}
			else
			{ 
				response.response = Serializer::serializeResponse(ErrorResponse("Unvalid meaage code"));;
			}
			this->sendMessage(clientSocket, response.response);
		}
		RequestInfo logout;
		logout.id = LOGOUT_REQUEST_CODE;
		this->_clients[clientSocket]->handleRequest(logout);
		this->_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		RequestInfo logout;
		logout.id = LOGOUT_REQUEST_CODE;
		this->_clients[clientSocket]->handleRequest(logout);
		this->_clients.erase(clientSocket);
		closesocket(clientSocket);
	}
}

bool Communicator::validPort(int port)
{
	return port <= MAX_PORT && port >= MIN_PORT;
}

RequestInfo Communicator::recvMessage(SOCKET sock)
{
	RequestInfo message = { 0 };
	int dataLength = 0;
	char* buffer = nullptr;

	recv(sock, (char*)&message.id, 1, 0);
	recv(sock, (char *)&dataLength, sizeof(int), 0);

	buffer = new char[dataLength + 1];
	buffer[dataLength] = 0;
	recv(sock, buffer, dataLength, 0);
	message.buffer.message = std::string(buffer);
	message.buffer.header = message.id;
	delete[] buffer;

	return message;
}

void Communicator::sendMessage(SOCKET sock, Buffer response)
{
	char* buffer = nullptr;
	int dataSize = 0;

	dataSize  = response.message.size();
	buffer = new char[dataSize + MESSAGE_HEADR_SIZE];
	buffer[0] = response.header;
	memcpy(buffer + 1, &dataSize, sizeof(int));
	memcpy(buffer + MESSAGE_HEADR_SIZE - 1, response.message.c_str(), dataSize);
	send(sock, buffer, dataSize + MESSAGE_HEADR_SIZE, 0);
	delete[] buffer;
}
