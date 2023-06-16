#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include "History.h"
#include "Question.h"


#define PUBLIC true 
#define PRIVATE false


const struct QuestionStruct;
class Question;

typedef struct Category
{
	std::string categoryName;
	bool permission;
	int creatorId;
}Category;



class IDatabase 
{
public:
	// Users:
	virtual bool doesUserExist(std::string username) const = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) const = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
	
	// Categories:
	virtual void addNewCategory(Category category, const std::string& username) = 0;
	virtual bool doesPublicCategoryExist(std::string categoryName) const = 0;
	virtual bool doesPrivateCategoryExist(const std::string& categoryName, const std::string& username) const = 0;
	virtual std::map<int, std::string> getPublicCategories() const = 0;
	virtual std::map<int, std::string> getPrivagteCategories(const std::string& username) const = 0;
	virtual void deleteCategory(int categoryId, const std::string& username) = 0;

	
	// Questions:
	virtual void addNewQuestion(int categorieId, std::string  username, QuestionStruct question) = 0;
	virtual std::vector<Question> getCategoryQuestions(int categoryId, const std::string& username) const = 0;
	virtual void deleteQuestion(int categoryId, const std::string& username, const std::string& question) = 0;
	
	// History:
	virtual void addNewHistory(const std::string& username, History history) = 0;
	virtual std::vector<History> getUserLastFiveHistory(const std::string& username) const = 0;
	virtual std::vector<History> getCategoryHistory(int categoryId) const = 0;
	
	// Statistics:
	virtual void createStatistics(int userId) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) const = 0;
	virtual int getNumOfCorrectAnswers(std::string username) const = 0;
	virtual int getNumOfTotalAnswers(std::string username) const = 0;
	virtual int getNumOfPlayerGames(std::string username) const = 0;
	virtual int getPlayerScore(std::string username) const = 0;
	virtual std::map<std::string, int> getHighScores(int numberOfUsers) const = 0;
private:
	virtual void updatUserStatistics(const std::string& username, int correctAnswers, int totalAnswers, double averageTime) = 0;
};