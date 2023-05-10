#pragma once
#include "sqlite3.h"
#include "IDatabase.h"
#include "SqliteUtilities.h"


#define DB_FILE_PATH "Trivia.sqlite"
#define TABLES_PATH "tables.sql"
#define QUESTION "QUESTION"
#define FIRST_ANSWER "FIRST_ANSWER"
#define SECOND_ANSWER "SECOND_ANSWER"
#define THIRD_ANSWER "THIRD_ANSWER"
#define FOURTH_ANSWER "FOURTH_ANSWER"
#define CATEGORY_ID "CATEGORY_ID"
#define RANK "RANK"
#define AVERAGE_TIME "AVERAGE_TIME"
#define NUMBER_OF_ANSWERS "NUMBER_OF_ANSWERS"
#define NUMBER_OF_CORRECT_ANSWERS "NUMBER_OF_CORRECT_ANSWERS"
#define CREATION_DATE "CREATION_DATE"
#define SCORE "SCORE"
#define PASSWORD "PASSWORD"
#define ID "ID" 


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	// Users:
	bool doesUserExist(std::string username) const;
	bool doesPasswordMatch(std::string username, std::string password) const;
	void addNewUser(std::string username, std::string password, std::string email);

	// Categories:
	void addNewCategory(Category category);
	bool doesCategoryExist(std::string categoryName) const;

	// Questions:
	void addNewQuestion(std::string categoryName, std::string username, Question question);
	std::vector<Question> getCategoryQuestions(const std::string& categoryName) const;

	// History:
	void addNewHistory(int userId, History history);
	std::vector<History> getUserLastFiveHistory(int usrId) const;
	std::vector<History> getCategoryHistory(const std::string& categoryname) const;

	// Statistics:
	float getPlayerAverageAnswerTime(std::string username) const;
	int getNumOfCorrectAnswers(std::string username) const;
	int getNumOfTotalAnswers(std::string username) const;
	int getNumOfPlayerGames(std::string username) const;
	int getPlayerScore(std::string username) const;
	std::vector<int> getHighScores(int numberOfUsers) const;

private:
	sqlite3* _db;

	// Statistics:
	 void updatUserStatistics(const std::string& username, int correctAnswers, int totalAnswers, double averageTime);


	SqliteCommand createDbCommand(std::string query, int(*collback)(void*, int, char**, char**) = nullptr, void* data = nullptr) const;
	int getUserId(std::string username) const;
	int getCategoryId(const std::string& categoryName) const;
	int getCategoryCreatorId(const std::string& categoryName) const;


	// Collbacks:
	static int boolCollback(void* data, int argc, char** argv, char** azColName);
	static int intCollback(void* data, int argc, char** argv, char** azColName);
	static int floatCollback(void* data, int argc, char** argv, char** azColName);
	static int getUserPasswordCollback(void* data, int argc, char** argv, char** azColName);
	static int idCollback(void* data, int argc, char** argv, char** azColName);
	static int questionsCollback(void* data, int argc, char** argv, char** azColName);
	static int historiesCollback(void* data, int argc, char** argv, char** azColName);
	static int scoreVectorCollback(void* data, int argc, char** argv, char** azColName);
};