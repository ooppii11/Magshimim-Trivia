#include "Communicator.h"
#include <iostream>
#include <thread>

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
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	std::string startMessage = START_MESSAGE;
	std::string clientRequest = "";

	try
	{
		send(clientSocket, startMessage.c_str(), startMessage.size(), 0); 
		clientRequest = recvMessage(clientSocket, sizeof(START_MESSAGE));

		if (clientRequest != START_MESSAGE)
		{
			throw std::exception("Client doesn't send 'Hello'");
		}
		std::cout << clientRequest << std::endl;
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}

bool Communicator::validPort(int port)
{
	return port <= MAX_PORT && port >= MIN_PORT;
}

std::string Communicator::recvMessage(SOCKET sock, int size)
{
	char* buffer = nullptr;
	std::string message = "";

	buffer = new char[size + 1];
	buffer[size] = 0;

	recv(sock, buffer, size, 0);

	message = std::string(buffer);
	delete[] buffer;
	return message;
}
