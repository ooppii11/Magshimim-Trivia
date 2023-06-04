#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include "JsonRequestPacketDeserializer.h"

#define PORT 6666

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.run(PORT);
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	return 0;
}
