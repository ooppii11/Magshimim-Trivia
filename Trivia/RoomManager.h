#pragma once
#include <map>
#include "Room.h"

typedef unsigned int roomID;

class RoomManager
{
public:
	int createRoom(LoggedUser user, RoomData data);
	void deleteRoom(roomID id);
	unsigned int getRoomState(roomID id);
	std::vector<RoomData> getRooms();
	Room& getRoom(roomID id);
private:
	std::map<roomID, Room> _rooms;

	unsigned int createRoomId();
	bool alreadyExists(unsigned int id);
};