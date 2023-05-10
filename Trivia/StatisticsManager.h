#pragma once
#include "IDatabase.h"
#include <vector>
#include <memory>

class StatisticsManager 
{
public:
	StatisticsManager(std::shared_ptr<IDatabase> db);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);

private:
	std::shared_ptr<IDatabase> _database;
};