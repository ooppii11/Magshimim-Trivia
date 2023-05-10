#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase> db) : _database(db) {}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	return std::vector<std::string>();
}
