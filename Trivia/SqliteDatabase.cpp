#include "SqliteDatabase.h"
#include "SqliteUtilities.h"

SqliteDatabase::SqliteDatabase()
{
	int response = sqlite3_open(DB_FILE_PATH, &this->_db);
	if (response != SQLITE_OK)
	{
		this->_db = nullptr;
		throw std::exception("Error while oprn 'Trivia.sqlite' db");
	}
	SqliteUtilities::executeFile(SqliteFileCommands{ TABLES_PATH, {this->_db, nullptr, nullptr} });
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
		throw std::exception("User doesn't exist!");
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
		throw std::exception("User already exist!");
	}

	query = "INSERT INTO USERS(USERNAME, PASSWORD, GMAIL) VALUES(\"" + username + "\", \"" + \
		password + "\", \"" + email + "\");";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

void SqliteDatabase::addNewCategory(Category category)
{
	SqliteCommand command;
	std::string query = "";

	if (this->doesCategoryExist(category.categoryName))
	{
		throw std::exception("Category already exist!");
	}

	query = "INSERT INTO CATEGORIES(NAME, PERMISSION, CREATOR_ID) VALUES(\"" + category.categoryName + "\", " + \
		(category.permission ? "true" : "false") + ", " + std::to_string(category.creatorId) + ");";

	command = createDbCommand(query);
	SqliteUtilities::executeCommand(command);
}

bool SqliteDatabase::doesCategoryExist(std::string categoryName) const
{
	SqliteCommand command;
	bool categoryExist = false;
	std::string query = "";

	query = "SELECT ID "
		"FROM CATEGORIES "
		"WHERE NAME = \"" + categoryName + "\";";

	command = createDbCommand(query, SqliteDatabase::boolCollback, &categoryExist);
	SqliteUtilities::executeCommand(command);
	return categoryExist;
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


int SqliteDatabase::boolCollback(void* data, int argc, char** argv, char** azColName)
{
	*((bool*)data) = true;
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
