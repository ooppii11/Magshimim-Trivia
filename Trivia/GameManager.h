#pragma once
#include "Game.h"
#include <vector>
#include "IDatabase.h"
#include "Room.h"


class GameManager
{
public:
	GameManager(std::shared_ptr<IDatabase> database);

	Game createGame(Room room);
	void deleteGame(int gameId);

private:
	std::shared_ptr<IDatabase> _database;
	std::vector<Game> _games;

};

