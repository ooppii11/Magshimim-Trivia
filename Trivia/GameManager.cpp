#include "GameManger.h"

GameManager::GameManager(std::shared_ptr<IDatabase> db) :
	_database(db) {}

Game GameManager::createGame(Room room, LoggedUser admin)
{
	std::vector<Question> questions;
	RoomData roomData = room.getRoomData();

	for (auto it : this->_database->getCategoryQuestions(room.getRoomData().categorieId, admin.getUsername()))
	{
		questions.push_back(Question(it));
	}
	return Game(roomData.id, room.getAllUsers(), questions);
}

void GameManager::deleteGame(int gameId)
{
	for (auto it = this->_games.begin(); it != this->_games.end(); it++)
	{
		if (it->getGameId() == gameId)
		{
			this->_games.erase(it);
		}
	}
}
