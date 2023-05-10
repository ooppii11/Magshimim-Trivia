#pragma once
#include "IDatabase.h"
#include <vector>
#include <memory>

class StatisticsManager 
{
public:
	StatisticsManager(const std::shared_ptr<IDatabase> db);
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string username) const;

private:
	std::shared_ptr<IDatabase> _database;
};