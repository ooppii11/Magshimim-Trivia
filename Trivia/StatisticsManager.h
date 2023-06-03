#pragma once
#include "IDatabase.h"
#include <vector>
#include <memory>
#include <map>

class StatisticsManager 
{
public:
	StatisticsManager(std::shared_ptr<IDatabase> db);
	std::map<std::string, int> getHighScore(int numOfScores) const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;

private:
	std::shared_ptr<IDatabase> _database;
};