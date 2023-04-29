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


private:
	sqlite3* _db;

	SqliteCommand createDbCommand(std::string query, int(*collback)(void*, int, char**, char**) = nullptr, void* data = nullptr) const;

	// Usesrs collback:
	static int userExistCollback(void* data, int argc, char** argv, char** azColName);
	static int getUserPasswordCollback(void* data, int argc, char** argv, char** azColName);
};