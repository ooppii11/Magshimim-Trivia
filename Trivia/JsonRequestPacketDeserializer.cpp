#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "messageException.h"
#include <fstream>
#include <iostream>
using json = nlohmann::json;


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
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

addCategorie Deserializer::addCategorieToUser(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		addCategorie temp;
		temp.categorieName = data["categorieName"];
		temp.permission = data["permission"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

removeCategorie Deserializer::removeCategorieFromUser(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		removeCategorie temp;
		temp.categorieName = data["categorieName"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}

addQuestion Deserializer::addQuestionToUserCategorie(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		addQuestion temp;
		temp.categorieName = data["categorieName"];
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

removeQuestion Deserializer::removeQuestionFromUserCategorie(const Buffer& buffer)
{
	try
	{
		json data = json::parse(buffer.message);
		removeQuestion temp;
		temp.categorieName = data["categorieName"];
		temp.questionName = data["questionName"];
		return temp;
	}
	catch (json::exception& e)
	{
		throw messageException("Error: Invalid massege");
	}
}
