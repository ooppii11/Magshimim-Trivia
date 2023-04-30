#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>


#define DELIMITER ";" 


typedef struct CommandSettings
{
	sqlite3* db;
	int(*collback)(void*, int, char**, char**) = nullptr;
	void* data = nullptr;
} CommandSettings;


typedef struct SqliteCommand
{
	std::string query;
	CommandSettings settings;
} SqliteCommand;



typedef struct SqliteFileCommands
{
	std::string filePath;
	CommandSettings settings;
} SqliteFileCommands;


class SqliteUtilities
{
public:
	static void executeCommand(SqliteCommand command);
	static void executeFile(SqliteFileCommands fileCommands);
	static void executeCommands(std::vector<SqliteCommand> commands);
private:
	static std::vector<SqliteCommand> readFileCommands(SqliteFileCommands fileCommands);
	static std::vector<SqliteCommand> createCommandsVector(std::vector<std::string> queries, CommandSettings settings);
};