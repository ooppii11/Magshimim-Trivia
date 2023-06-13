#include "GameManager.h"

GameManager::GameManager(std::shared_ptr<IDatabase> database) :
	_database(database) {}

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
