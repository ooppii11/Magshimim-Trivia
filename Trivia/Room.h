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
	friend std::ostream& operator<<(std::ostream& os, const RoomData& data);
} RoomData;

class Room
{
public:
	void addUser(const LoggedUser user);
	void removeUser(const LoggedUser user);
	std::vector<std::string> getAllUsers() const;
	RoomData getRoomData();
	void setRoomData(const RoomData& data);
private:
	RoomData _metadata;
	std::vector<LoggedUser> _users;
};