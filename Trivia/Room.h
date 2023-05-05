#pragma once
#include <vector>
#include "LoggedUser.h"


typedef struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

class Room
{
public:
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();

private:
	RoomData _metadata;
	std::vector<LoggedUser> _users;
};