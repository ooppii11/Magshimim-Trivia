#pragma once
#include <map>
#include "Room.h"

typedef unsigned int roomID;

class RoomManager
{
public:
	void createRoom(const LoggedUser& user, const RoomData& data);
	void deleteRoom(const roomID id);
	unsigned int getRoomState(const roomID id);
	std::vector<RoomData> getRooms();
	Room& getRoom(const roomID id);
private:
	std::map<roomID, Room> _rooms;
};