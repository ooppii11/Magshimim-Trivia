#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;


LoginRequest Deserializer::deserializeLoginRequest(Buffer buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		LoginRequest temp;
		temp.username = data["username"];
		temp.password = data["password"];
		return temp;
	}
	catch (json::exception& e)
	{
		//TODO: need to return error type tat says the message is invalid
		std::cerr << e.what() << std::endl;
	}
}

SignupRequest Deserializer::deserializeSignupRequest(Buffer buffer)
{
	try 
	{
		json data = json::parse(buffer.message);
		SignupRequest temp;
		temp.username = data["username"];
		temp.password = data["password"];
		temp.email = data["email"];
		return temp;
	}
	catch (json::exception& e)
	{
		//TODO: need to return error type tat says the message is invalid
		std::cerr << e.what() << std::endl;
	}
}