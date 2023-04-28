#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>


typedef struct SqliteCommand
{
	sqlite3* db;
	std::string query;
	int(*collback)(void*, int, char**, char**) = nullptr;
	void* data = nullptr;
}SqliteCommand;


typedef struct SqliteFileCommands
{
	sqlite3* db;
	std::string filePath;
}SqliteFileCommands;

class SqliteUtilities
{
public:
	static void executeCommand(SqliteCommand command);
};