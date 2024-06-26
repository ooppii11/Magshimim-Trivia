#include "SqliteDatabase.h"
#include "SqliteUtilities.h"
#include "messageException.h"
#include <map>
#include "FileUtilities.h"


SqliteDatabase::SqliteDatabase()
{
	bool dbExsist = FileUtilities::fileExsists(DB_FILE_PATH);
	int response = sqlite3_open(DB_FILE_PATH, &this->_db);
	if (response != SQLITE_OK)
	{
		this->_db = nullptr;
		std::cerr << "Error while oprn 'Trivia.sqlite' db" << std::endl;
		throw std::exception("Error while oprn 'Trivia.sqlite' db");
	}
	SqliteUtilities::executeFile(SqliteFileCommands{ TABLES_PATH, {this->_db, nullptr, nullptr} });
	if (!dbExsist) {
		SqliteUtilities::executeFile(SqliteFileCommands{ INIT_DATA_PATH, {this->_db, nullptr, nullptr} });
	}
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}

bool SqliteDatabase::doesUserExist(std::string username) const
{
	SqliteCommand command;
	bool userExist = false;
	std::string query = "";

	query = "SELECT ID " 
			"FROM USERS "
			"WHERE USERNAME = \"" + username + "\";";

	command = createDbCommand(query, SqliteDatabase::boolCollback, &userExist);
	SqliteUtilities::executeCommand(command);
	return userExist;
}


bool SqliteDatabase::doesPasswordMatch(std::string username, std::string password) const
{
	SqliteCommand command;
	std::string userPassword = "";
	std::string query = "";

	if (!this->doesUserExist(username))
	{
		throw messageException("User doesn't exist!");
	}

	query = "SELECT PASSWORD "
			"FROM USERS "
			"WHERE USERNAME = \"" + username + "\";";

	command = createDbCommand(query, SqliteDatabase::getUserPasswordCollback, &userPassword);
	SqliteUtilities::executeCommand(command);
	return userPassword == password;
}

void SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
	SqliteCommand command;
	std::string query = "";
	
	if (this->doesUserExist(username))
	{
		std::cout << "User already exist!" << std::endl;
		throw messageException("User already exist!");
	}

	query = "INSERT INTO USERS(USERNAME, PASSWORD, EMAIL) VALUES(\"" + username + "\", \"" + \
		password + "\", \"" + email + "\");";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
	this->createStatistics(this->getUserId(username));
}

void SqliteDatabase::addNewCategory(Category category, const std::string& username)
{
	SqliteCommand command;
	std::string query = "";

	if (this->doesPublicCategoryExist(category.categoryName) || this->doesPrivateCategoryExist(category.categoryName, username))
	{
		throw messageException("Category already exist!");
	}

	query = "INSERT INTO CATEGORIES(NAME, PERMISSION, CREATOR_ID) VALUES(\"" + category.categoryName + "\", " + \
		(category.permission ? "true" : "false") + ", " + std::to_string(category.creatorId) + ");";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

bool SqliteDatabase::doesPublicCategoryExist(std::string categoryName) const
{
	SqliteCommand command;
	bool categoryExist = false;
	std::string query = "";

	query = "SELECT ID "
		"FROM CATEGORIES "
		"WHERE PERMISSION = True AND NAME = \"" + categoryName + "\";";

	command = createDbCommand(query, SqliteDatabase::boolCollback, &categoryExist);
	SqliteUtilities::executeCommand(command);
	return categoryExist;
}

bool SqliteDatabase::doesPrivateCategoryExist(const std::string& categoryName, const std::string& username) const
{
	SqliteCommand command;
	bool categoryExist = false;
	std::string query = "";

	query = "SELECT ID "
		"FROM CATEGORIES "
		"WHERE PERMISSION = False AND CREATOR_ID = " + std::to_string(this->getUserId(username)) + "NAME = \"" + categoryName + "\";";

	command = createDbCommand(query, SqliteDatabase::boolCollback, &categoryExist);
	SqliteUtilities::executeCommand(command);
	return categoryExist;
}

std::map<int, std::string> SqliteDatabase::getPublicCategories() const
{
	SqliteCommand command;
	std::map<int, std::string> categories;
	std::string query = "";

	query = "SELECT ID, NAME "
		"FROM CATEGORIES "
		"WHERE PERMISSION = \"True\";";

	command = createDbCommand(query, SqliteDatabase::categoriesCollback, &categories);
	SqliteUtilities::executeCommand(command);
	return categories;
}

std::map<int, std::string> SqliteDatabase::getPrivagteCategories(const std::string& username) const
{
	SqliteCommand command;
	std::map<int, std::string> categories;
	std::string query = "";

	query = "SELECT ID, NAME "
		"FROM CATEGORIES "
		"WHERE PERMISSION = \"False\" AND CREATOR_ID = " + std::to_string(this->getUserId(username)) + ";";

	command = createDbCommand(query, SqliteDatabase::categoriesCollback, &categories);
	SqliteUtilities::executeCommand(command);
	return categories;
}

void SqliteDatabase::deleteCategory(int categoryId, const std::string& username)
{
	SqliteCommand command;
	std::string query = "";
	int userId = 0;
	int creatorId = 0;

	creatorId = this->getCategoryCreatorId(categoryId);
	userId = this->getUserId(username);

	if (creatorId != userId) { throw messageException("Not your category"); }

	query = "DELETE FROM CATEGORIES  WHERE = ID = " + std::to_string(categoryId) + "; ";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

void SqliteDatabase::addNewQuestion(int categoryId, std::string username, QuestionStruct question)
{
	SqliteCommand command;
	std::string query = "";
	int uesrId = 0;
	int creatorId = 0;

	creatorId = this->getCategoryCreatorId(categoryId);
	uesrId = this->getUserId(username);

	if (uesrId != creatorId)
	{
		throw messageException("Not your category");
	}

	query = "INSERT INTO QUESTIONS("
				"CATEGORY_ID, "
				"QUESTION, "
				"CORRECT_ANSWER_INDEX,"
				"FIRST_ANSWER, "
				"SECOND_ANSWER, "
				"THIRD_ANSWER, "
				"FOURTH_ANSWER) "
		"VALUES("
			+ std::to_string(categoryId) + ", "
			"\"" + question.question + "\", "
			+ std::to_string(question.correctAnswerIndex) + ", "
			"\"" + question.firstAnswer + "\", "
			"\"" + question.thirdAnswer + "\", "
			"\"" + question.fourthAnswer + "\", "
			");";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

std::vector<Question> SqliteDatabase::getCategoryQuestions(int categoryId, const std::string& username) const
{
	SqliteCommand command;
	std::vector<Question> questions;
	std::string query = "";
	int uesrId = 0;
	int creatorId = 0;

	creatorId = this->getCategoryCreatorId(categoryId);
	uesrId = this->getUserId(username);

	if (uesrId != creatorId && this->getCategoryPermssion(categoryId) != PUBLIC)
	{
		throw messageException("Not your category");
	}

	query = "SELECT * "
			"FROM QUESTIONS ";
			"WHERE CATEGORY_ID = " + std::to_string(categoryId) + ";";

	command = createDbCommand(query, SqliteDatabase::questionsCollback , &questions);
	SqliteUtilities::executeCommand(command);
	return questions;
}

void SqliteDatabase::deleteQuestion(int categoryId, const std::string& username, const std::string& question)
{
	SqliteCommand command;
	std::string query = "";
	int userId = 0;
	int creatorId = 0;

	creatorId = this->getCategoryCreatorId(categoryId);
	userId = this->getUserId(username);

	if (creatorId != userId) { throw messageException("Not your category"); }

	query = "DELETE FROM QUESTIONS WHERE CATEGORY_ID = " + std::to_string(categoryId) + " AND QUESTION = \"" + question + "\";";
	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

void SqliteDatabase::addNewHistory(const std::string& username, History history)
{
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "INSERT INTO HISTORY("
				"USER_ID, "
				"CATEGORY_ID, "
				"RANK, "  
				"AVERAGE_TIME, "
				"NUMBER_OF_ANSWERS, "
				"NUMBER_OF_CORRECT_ANSWERS) "
			"VALUES("
				+ std::to_string(userId)  + ", "
				+ std::to_string(history.categoryId) + ", "
				+ std::to_string(history.rank) + ", "
				+ std::to_string(history.avergeTime) + ", "
				+ std::to_string(history.answers) + ", "
				+ std::to_string(history.correctAnswers) + ");";


	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
	this->updatUserStatistics(username, history.rank, history.correctAnswers, history.answers, history.avergeTime);
}

std::vector<History> SqliteDatabase::getUserLastFiveHistory(const std::string& username) const
{
	std::vector<History> lastHistories;
	SqliteCommand command;
	int userId = 0;
	std::string query = "";

	userId = this->getUserId(username);
	query = "SELECT CATEGORY_ID, RANK, AVERAGE_TIME, NUMBER_OF_ANSWERS, NUMBER_OF_CORRECT_ANSWERS, CREATION_DATE "
			"FROM HISTORY "
			"WHERE USER_ID = " + std::to_string(userId) + " LIMIT 5;";

	command = createDbCommand(query, SqliteDatabase::historiesCollback, &lastHistories);
	SqliteUtilities::executeCommand(command);
	return lastHistories;
}

std::vector<History> SqliteDatabase::getCategoryHistory(int categoryId) const
{
	std::vector<History> histories;
	SqliteCommand command;
	std::string query = "";

	query = "SELECT CATEGORY_ID, RANK, AVERAGE_TIME, NUMBER_OF_ANSWERS, NUMBER_OF_CORRECT_ANSWERS, CREATION_DATE "
			"FROM HISTORY "
			"WHERE CATEGORY_ID = " + std::to_string(categoryId) + ";";

	command = createDbCommand(query, SqliteDatabase::historiesCollback, &histories);
	SqliteUtilities::executeCommand(command);
	return histories;
}



void SqliteDatabase::updatUserStatistics(const std::string& username, int rank,  int correctAnswers, int totalAnswers, double averageTime)
{
	SqliteCommand command;
	std::string query = "";
	int userId = 0;
	int score = this->getPlayerScore(username);
	if (rank <= TOP_THREE)
	{
		score += RANK_ONE_SCORE - (rank - 1) * (ADD_SCORE);
	}
	else
	{
		score += ADD_SCORE;
	}

	userId = this->getUserId(username);
	float time = (this->getPlayerAverageAnswerTime(username));
	if (time == 0)
	{
		time += averageTime;
	}
	else
	{
		time += averageTime / 2;
	}
	correctAnswers += this->getNumOfCorrectAnswers(username);
	totalAnswers += this->getNumOfTotalAnswers(username);

	query = "UPDATE STATISTICS "
			"SET "
				"SCORE = " + std::to_string(score) +
				", AVERAGE_TIME = " + std::to_string(time) +
				", NUMBER_OF_ANSWERS = " + std::to_string(totalAnswers) +
				", NUMBER_OF_CORRECT_ANSWERS = " + std::to_string(correctAnswers) +
				", NUMBER_OF_GAMES = " + std::to_string(this->getNumOfPlayerGames(username) + 1) +
			" WHERE USER_ID = " + std::to_string(userId) + "; ";
		command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

SqliteCommand SqliteDatabase::createDbCommand(std::string query, int(*collback)(void*, int, char**, char**), void* data) const
{
	SqliteCommand command;

	command.query = query;
	command.settings.data = data;
	command.settings.db = this->_db;
	command.settings.collback = collback;

	return command;
}

int SqliteDatabase::getUserId(std::string username) const
{
	int userId = 0;
	SqliteCommand command;
	std::string query = "";

	query = "SELECT ID "
			"FROM USERS "
			"WHERE USERNAME = \"" +  username + "\";";

	command = createDbCommand(query, SqliteDatabase::idCollback, &userId);
	SqliteUtilities::executeCommand(command);
	return userId;
}

int SqliteDatabase::getCategoryId(const std::string& categoryName) const
{
	int categoryId;
	SqliteCommand command;
	std::string query = "";

	query = "SELECT * "
			"FROM CATEGORIES "
			"WHERE NAME = \"" + categoryName + "\";";

	command = createDbCommand(query, SqliteDatabase::idCollback, &categoryId);
	SqliteUtilities::executeCommand(command);
	return categoryId;
}

int SqliteDatabase::getCategoryCreatorId(int categoryId) const
{
	int creatorId;
	SqliteCommand command;
	std::string query = "";

	query = "SELECT CREATOR_ID  "
		"FROM CATEGORIES "
		"WHERE  ID = " + std::to_string(categoryId) + ";";

	command = createDbCommand(query, SqliteDatabase::idCollback, &creatorId);
	SqliteUtilities::executeCommand(command);
	return creatorId;
}

bool SqliteDatabase::getCategoryPermssion(int categoryId) const
{
	bool permssion = PRIVATE;
	SqliteCommand command;
	std::string query = "";

	query = "SELECT PERMISSION  "
		"FROM CATEGORIES "
		"WHERE  ID = " + std::to_string(categoryId) + ";";

	command = createDbCommand(query, SqliteDatabase::categoryPremssionCollback, &permssion);
	SqliteUtilities::executeCommand(command);
	return permssion;
}

int SqliteDatabase::categoryPremssionCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 1 && std::string(azColName[0]) == PERMISSION)
	{
		if(argv[0])
		{ 
			*((bool*)data) = true;
		}
		else
		{
			*((bool*)data) = false;
		}
	}
	return 0;
}

int SqliteDatabase::boolCollback(void* data, int argc, char** argv, char** azColName)
{
	*((bool*)data) = true;
	return 0;
}

int SqliteDatabase::intCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 1)
	{
		*((int*)data) = atoi(argv[0]);
	}
	return 0;
}

int SqliteDatabase::floatCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 1)
	{
		*((float*)data) = atoi(argv[0]);
	}
	return 0;
}


int SqliteDatabase::getUserPasswordCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 1 && std::string(azColName[0]) == PASSWORD)
	{
		*((std::string*)data) = std::string(argv[0]);
	}
	return 0;
}

int SqliteDatabase::idCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 1 && std::string(azColName[0]) == ID)
	{
		*((int*)data) = atoi(argv[0]);
	}
	return 0;
}

int SqliteDatabase::questionsCollback(void* data, int argc, char** argv, char** azColName)
{
	int i = 0;
	QuestionStruct question;
	question.correctAnswerIndex = 0;

	for (i = 0; i < argc; i++)
	{
		if(std::string(azColName[i]) == QUESTION) { question.question = std::string(argv[i]); }
		else if (std::string(azColName[i]) == CORRECT_ANSWER_INDEX) { question.correctAnswerIndex = atoi(argv[i]); }
		else if(std::string(azColName[i]) == FIRST_ANSWER) { question.firstAnswer = std::string(argv[i]); }
		else if(std::string(azColName[i]) == SECOND_ANSWER) { question.secondAnswer = std::string(argv[i]); }
		else if(std::string(azColName[i]) == THIRD_ANSWER) { question.thirdAnswer = std::string(argv[i]); }
		else if(std::string(azColName[i]) == FOURTH_ANSWER) { question.fourthAnswer = std::string(argv[i]); }
	}
	(*(std::vector<Question> *)data).push_back(Question(question));
	return 0;
}

int SqliteDatabase::historiesCollback(void* data, int argc, char** argv, char** azColName)
{
	int i = 0;
	History history;

	for (i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == CATEGORY_ID) { history.categoryId = atoi(argv[i]); }
		else if (std::string(azColName[i]) == RANK) { history.rank = atoi(argv[i]); }
		else if (std::string(azColName[i]) == AVERAGE_TIME) { history.avergeTime = atoi(argv[i]); }
		else if (std::string(azColName[i]) == NUMBER_OF_ANSWERS) { history.answers = atoi(argv[i]); }
		else if (std::string(azColName[i]) == NUMBER_OF_CORRECT_ANSWERS) { history.correctAnswers = atoi(argv[i]); }
		else if (std::string(azColName[i]) == CREATION_DATE) {  history.creationDate = std::string(argv[i]); }
	}
	(*(std::vector<History> *)data).push_back(history);
	return 0;
}

int SqliteDatabase::scoreCollback(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 2 && std::string(azColName[0]) == SCORE && std::string(azColName[1]) == USERNAME)
	{
		(*(std::map<std::string, int>*)data)[std::string(argv[1])] = atoi(argv[0]);
	}
	return 0;
}

int SqliteDatabase::categoriesCollback(void* data, int argc, char** argv, char** azColName)
{
	int i = 0;
	std::pair<int, std::string> category;
	for (i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == NAME) { category.second = std::string(argv[i]); }
		else if (std::string(azColName[i]) == ID) { category.first = atoi(argv[i]); }
	}
	(*(std::map<int, std::string> *)data).insert(category);
	return 0;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string username) const
{
	float averageTime = 0.0;
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "SELECT AVERAGE_TIME "
		"FROM STATISTICS "
		"WHERE USER_ID = " + std::to_string(userId) + ";";

	command = createDbCommand(query, SqliteDatabase::floatCollback, &averageTime);
	SqliteUtilities::executeCommand(command);
	return averageTime;
}

int SqliteDatabase::getNumOfCorrectAnswers(std::string username) const
{
	int correctAnswers = 0;
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "SELECT NUMBER_OF_CORRECT_ANSWERS "
			"FROM STATISTICS "
			"WHERE USER_ID = " + std::to_string(userId) + ";";

	command = createDbCommand(query, SqliteDatabase::intCollback, &correctAnswers);
	SqliteUtilities::executeCommand(command);
	return correctAnswers;
}

int SqliteDatabase::getNumOfTotalAnswers(std::string username) const
{
	int answers = 0;
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "SELECT NUMBER_OF_ANSWERS "
			"FROM STATISTICS "
			"WHERE USER_ID = " + std::to_string(userId) + ";";

	command = createDbCommand(query, SqliteDatabase::intCollback, &answers);
	SqliteUtilities::executeCommand(command);
	return answers;
}

int SqliteDatabase::getNumOfPlayerGames(std::string username) const
{
	int games = 0;
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "SELECT NUMBER_OF_GAMES "
			"FROM STATISTICS "
			"WHERE USER_ID = " + std::to_string(userId) + ";";

	command = createDbCommand(query, SqliteDatabase::intCollback, &games);
	SqliteUtilities::executeCommand(command);
	return games;
}

int SqliteDatabase::getPlayerScore(std::string username) const
{
	int score = 0;
	SqliteCommand command;
	std::string query = "";
	int userId = 0;

	userId = this->getUserId(username);
	query = "SELECT SCORE "
			"FROM STATISTICS "
			"WHERE USER_ID = " + std::to_string(userId) + ";";

	command = createDbCommand(query, SqliteDatabase::intCollback, &score);
	SqliteUtilities::executeCommand(command);
	return score;
}

std::map<std::string, int> SqliteDatabase::getHighScores(int numberOfUsers) const
{
	SqliteCommand command;
	std::string query = "";
	std::map<std::string, int> scores;

	query = "SELECT STATISTICS.SCORE, USERS.USERNAME "
			"FROM STATISTICS "
			"JOIN USERS ON USERS.ID = STATISTICS.USER_ID "
			"ORDER BY SCORE DESC LIMIT " + std::to_string(numberOfUsers)  + ";";

	command = createDbCommand(query, SqliteDatabase::scoreCollback, &scores);
	SqliteUtilities::executeCommand(command);
	return scores;
}

void SqliteDatabase::createStatistics(int userId)
{
	SqliteCommand command;
	std::string query = "";

	query = "INSERT INTO STATISTICS"
		"(\"USER_ID\", \"SCORE\", \"AVERAGE_TIME\", \"NUMBER_OF_GAMES\", \"NUMBER_OF_ANSWERS\", \"NUMBER_OF_CORRECT_ANSWERS\")"
		"VALUES(" +std::to_string(userId) + ", 0, 0, 0, 0, 0); ";
	
	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}
