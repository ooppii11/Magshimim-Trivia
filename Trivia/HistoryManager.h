#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IDatabase.h"
#include "History.h"



class HistoryManager
{
public:
	HistoryManager(std::shared_ptr<IDatabase> db);
	void addNewHistory(const std::string& username, History& history);
	std::vector<History> getUserLastFiveHistory(const std::string& username) const;
	std::vector<History> getCategoryHistory(const unsigned int categorieId) const;

private:
	std::shared_ptr<IDatabase> _database;
};