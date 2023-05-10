#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase> db) : _database(db) {}

std::vector<std::string> StatisticsManager::getHighScore() const
{
	return std::vector<std::string>();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string username) const
{
	return std::vector<std::string>();
}
