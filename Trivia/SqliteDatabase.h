#pragma once
#include "sqlite3.h"
#include "IDatabase.h"
#include "SqliteUtilities.h"


#define PASSWORD "PASSWORD"
#define DB_FILE_PATH "Trivia.sqlite"
#define TABLES_PATH "tables.sql"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();

	// Users:
	bool doesUserExist(std::string username) const override;
	bool doesPasswordMatch(std::string username, std::string password) const override;
	void addNewUser(std::string username, std::string password, std::string email) override;

	// Categories:
	virtual void addNewCategory(Category category);
	virtual bool doesCategoryExist(std::string categoryName) const;

	// Questions:
	virtual void addNewQuestion(std::string CategoryName, int userId, Question question);
	virtual void removeQuestion(int questionId, int userId) = 0;
	virtual std::vector<Question> getCategoryQuestions(std::string CategoryName, int numberOfQuestions) const;

	// History:
	virtual void addNewHistory(History history);
	virtual std::vector<History> getUserLastFiveHistory(int usrId) const;
	virtual std::vector<History> getCategoryHistory(int categoryId) const;

	// Statistics:
	virtual void updatUserNumberofAnswer(int userId, bool correctAnswer, double time);
	virtual void updatUserNumberofgames(int userId);

	virtual float getPlayerAverageAnswerTime(std::string username) const;
	virtual int getNumOfCorrectAnswers(std::string username) const;
	virtual int getNumOfTotalAnswers(std::string username) const;
	virtual int getNumOfPlayerGames(std::string username) const;
	virtual int getPlayerScore(std::string username) const;
	virtual std::vector<float> getHighScores(int numberOfUsers) const;

private:
	sqlite3* _db;

	SqliteCommand createDbCommand(std::string query, int(*collback)(void*, int, char**, char**) = nullptr, void* data = nullptr) const;

	// Usesrs collback:
	static int boolCollback(void* data, int argc, char** argv, char** azColName);
	static int getUserPasswordCollback(void* data, int argc, char** argv, char** azColName);
};