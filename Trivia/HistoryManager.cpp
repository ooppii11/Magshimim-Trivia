#include "HistoryManager.h"

HistoryManager::HistoryManager(std::shared_ptr<IDatabase> db)
{
}

void HistoryManager::addNewHistory(const std::string& username, History& history)
{
	this->_database->addNewHistory(username, history);
}

std::vector<History> HistoryManager::getUserLastFiveHistory(const std::string& username) const
{
	return this->_database->getUserLastFiveHistory(username);
}

std::vector<History> HistoryManager::getCategoryHistory(const unsigned int categoryId) const
{
	return this->_database->getCategoryHistory(categoryId);
}




