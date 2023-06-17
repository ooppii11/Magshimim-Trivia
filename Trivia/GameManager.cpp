#include "GameManager.h"
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
	Game game(roomData.id, room.getAllUsers(), questions, roomData.timePerQuestion);
	this->_games.push_back(game);
	return game;
}

Game& GameManager::getGameById(unsigned int id)
{
	for (auto it = this->_games.begin(); it != this->_games.end(); it++)
	{
		if (it->getGameId() == id)
		{
			return *it;
		}
	}
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
