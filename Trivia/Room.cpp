#include "Room.h"
#include <algorithm>
#include <iostream>

void Room::addUser(LoggedUser user)
{
	this->_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	auto userIt = std::find(this->_users.begin(), this->_users.end(), user);
	if (userIt == this->_users.end())
	{
		throw std::exception("User isn't in the room");
	}
	this->_users.erase(userIt);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> usersNames;

	for (auto user : this->_users)
	{
		usersNames.push_back(user.getUsername());
	}
	return usersNames;
}

std::ostream& operator<<(std::ostream& os, const RoomData& data)
{
	return os << data.name;
}
