#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase> db) : _database(db) {}

std::map<std::string, int> StatisticsManager::getHighScore(int numOfScores) const
{ 
	return this->_database->getHighScores(numOfScores);
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::vector<std::string> userStatistics;
	userStatistics.push_back(std::to_string(this->_database->getPlayerAverageAnswerTime(username)));
	userStatistics.push_back(std::to_string(this->_database->getNumOfCorrectAnswers(username)));
	userStatistics.push_back(std::to_string(this->_database->getNumOfTotalAnswers(username)));
	userStatistics.push_back(std::to_string(this->_database->getNumOfPlayerGames(username)));
	
	return userStatistics;
}
