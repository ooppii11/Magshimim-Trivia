#include "RoomManager.h"
#include <functional> 
#include <cmath>
int RoomManager::createRoom(LoggedUser user, RoomData data)
{
	Room r;
	data.id = createRoomId();
	r.setRoomData(data);
	r.addUser(user);
	this->_rooms[data.id] = r;
	return data.id;
}

unsigned int RoomManager::createRoomId()
{
	std::hash<int> hasher;
	unsigned int id = 0;
	int i = 0;
	do
	{
		id = 0;
		auto hshed = hasher(this->_rooms.size() + i);
		unsigned int X = (unsigned int)std::pow(2, (sizeof(unsigned int) * 8));
		id = (unsigned int)hshed % ((unsigned int)std::pow(2, (sizeof(unsigned int) * 8)) -1);
		i++;
	} while (this->alreadyExists(id));
	return id;
}

bool RoomManager::alreadyExists(unsigned int id)
{
	for (auto UsedIds : this->_rooms)
	{
		if (UsedIds.first == id)
		{
			return true;
		}
	}
	return false;
}

void RoomManager::deleteRoom(roomID id)
{
	this->_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(roomID id)
{
	return this->_rooms[id].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> rooms;
	for (auto room : this->_rooms)
	{
		rooms.push_back(room.second.getRoomData());
	}
	return rooms;
}

Room& RoomManager::getRoom(roomID id)
{
	return this->_rooms[id];
}