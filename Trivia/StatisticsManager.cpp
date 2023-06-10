#include "StatisticsManager.h"
#include <map>

StatisticsManager::StatisticsManager(std::shared_ptr<IDatabase> db) : _database(db) {}

std::map<std::string, int> StatisticsManager::getHighScore(int numOfScores) const
{ 
	return this->_database->getHighScores(numOfScores);
}

std::map<std::string, int> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::map<std::string, int> userStatistics;
	userStatistics["PlayerAverageAnswerTime"] = this->_database->getPlayerAverageAnswerTime(username);
	userStatistics["NumOfCorrectAnswers"] = this->_database->getNumOfCorrectAnswers(username);
	userStatistics["NumOfTotalAnswers"] = this->_database->getNumOfTotalAnswers(username);
	userStatistics["NumOfPlayerGames"] = this->_database->getNumOfPlayerGames(username);
	
	return userStatistics;
}
