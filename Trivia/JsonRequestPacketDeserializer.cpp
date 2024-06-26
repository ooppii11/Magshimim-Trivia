#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "messageException.h"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

//json::parse("");
/*
Json::Reader reader;
Json::Value root;
string json = "";
bool parseSuccess = reader.parse(json, root, false);
if (parseSuccess) {}
*/

LoginRequest Deserializer::deserializeLoginRequest(const Buffer& buffer)
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
		throw messageException("Error: Invalid massege");
	}
}

SignupRequest Deserializer::deserializeSignupRequest(const Buffer& buffer)
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
		throw messageException("Error: Invalid massege");
	}
}

GetPlayersInRoomRequest Deserializer::deserializeGetPlayersRequest(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		GetPlayersInRoomRequest temp;
		temp.roomId = data["roomId"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

JoinRoomRequest Deserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		JoinRoomRequest temp;
		temp.roomId = data["roomId"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

CreateRoomRequest Deserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		CreateRoomRequest temp;
		temp.roomName = data["roomName"];
		temp.maxUsers = data["maxUsers"];
		temp.questionCount = data["questionCount"];
		temp.answerTimeout = data["answerTimeout"];
		temp.categorieId = data["categorieId"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

addCategorieRequest Deserializer::addCategorieToUser(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		addCategorieRequest temp;
		temp.categoryName = data["categorieName"];
		temp.permission = data["permission"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

removeCategorieRequest Deserializer::removeCategorieFromUser(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		removeCategorieRequest temp;
		temp.categorieId = data["categorieId"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

addQuestionRequest Deserializer::addQuestionToUserCategorie(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		addQuestionRequest temp;
		temp.categorieId = data["categorieId"];
		temp.questionName = data["questionName"];
		temp.correctAnswerIndex = data["correctAnswerIndex"];
		for (int i = 0; i < NUM_OF_ANSWERS; i++)
		{
			temp.answers[i] = data["answer_" + std::to_string(i)];
		}
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

removeQuestionRequest Deserializer::removeQuestionFromUserCategorie(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		removeQuestionRequest temp;
		temp.categorieId = data["categorieId"];
		temp.questionName = data["questionName"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

SubmitAnswerRequest Deserializer::deserializeSubminAnswerRequest(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		SubmitAnswerRequest temp;
		temp.answerIndex = data["answerIndex"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}
