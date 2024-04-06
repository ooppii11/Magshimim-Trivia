#include "Room.h"
#include <algorithm>
#include <iostream>
#include "messageException.h"

void Room::addUser(const LoggedUser user)
{
	this->_users.push_back(user);
}

void Room::removeUser(const LoggedUser user)
{
	auto userIt = std::find(this->_users.begin(), this->_users.end(), user);
	if (userIt == this->_users.end())
	{
		throw messageException("User isn't in the room");
	}
	this->_users.erase(userIt);
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> usersNames;

	for (auto user : this->_users)
	{
		usersNames.push_back(user.getUsername());
	}
	return usersNames;
}

RoomData Room::getRoomData()
{
	return this->_metadata;
}

void Room::setRoomData(const RoomData& data)
{
	this->_metadata = data;
}

std::ostream& operator<<(std::ostream& os, const RoomData& data)
{
	return os << "{" 
		<< "\"Id\": " << data.id << ", "
		<< "\"Name\": " << "\"" + data.name + "\"" << ", "
		<< "\"CategorieId\": " << data.categorieId << ", "
		<< "\"IsActive\": " << data.isActive << ", "
		<< "\"Time\": " << data.timePerQuestion << ", "
		<< "\"NumOfQuestions\": " << data.numOfQuestionsInGame << ", "
		<< "\"MaxPlayers\": " << data.maxPlayers << "}";
}
