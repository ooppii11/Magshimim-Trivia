#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	Room r;
	r.setRoomData(data);
	r.addUser(user);
	this->_rooms[data.id] = r;
}

void RoomManager::deleteRoom(const roomID id)
{
	this->_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(const roomID id)
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

Room& RoomManager::getRoom(const roomID id)
{
	return this->_rooms[id];
}