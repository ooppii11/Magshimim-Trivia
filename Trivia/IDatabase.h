#pragma once
#include <string>
#include <vector>
#include <ctime>


typedef struct Question
{
	std::string question;
	int correctAnswerIndex;
	std::string firstAnswer;
	std::string secondAnswer;
	std::string thirdAnswer;
	std::string fourthAnswer;
} Question;


typedef struct History
{
	int categoryId;
	int rank;
	double avergeTime;
	int answers;
	int correctAnswers;
	time_t creationDate;
} History;


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
	virtual void addNewCategory(Category category) = 0;
	virtual bool doesCategoryExist(std::string categoryName) const = 0;

	// Questions:
	virtual void addNewQuestion(std::string categoryName, int userId, Question question) = 0;
	virtual std::vector<Question> getCategoryQuestions(const std::string& CategoryName) const = 0;

	// History:
	virtual void addNewHistory(int userId, History history) = 0;
	virtual std::vector<History> getUserLastFiveHistory(int usrId) const = 0;
	virtual std::vector<History> getCategoryHistory(const std::string& categoryname) const = 0;

	// Statistics:
	virtual void updatUserNumberofAnswer(int userId, bool correctAnswer, double time) = 0;
	virtual void updatUserNumberofgames(int userId) = 0;

	virtual float getPlayerAverageAnswerTime(std::string username) const = 0;
	virtual int getNumOfCorrectAnswers(std::string username) const = 0;
	virtual int getNumOfTotalAnswers(std::string username) const = 0;
	virtual int getNumOfPlayerGames(std::string username) const = 0;
	virtual int getPlayerScore(std::string username) const = 0;
	virtual std::vector<float> getHighScores(int numberOfUsers) const = 0;

};