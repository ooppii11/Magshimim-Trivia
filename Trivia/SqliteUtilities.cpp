#include "SqliteUtilities.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <iostream>


void SqliteUtilities::executeCommand(SqliteCommand command)
{
	int res = 0;
	char** errMessage = nullptr;

	res = sqlite3_exec(command.settings.db, command.query.c_str(), command.settings.collback, command.settings.data, errMessage);
	if (res != SQLITE_OK)
	{
		std::cerr << "DB ERORR" << std::endl;
		throw std::exception("DB ERORR");
	}
}

void SqliteUtilities::executeFile(SqliteFileCommands fileCommands)
{
	SqliteUtilities::executeCommands(SqliteUtilities::readFileCommands(fileCommands));
}

void SqliteUtilities::executeCommands(std::vector<SqliteCommand> commands)
{
	for (auto& command : commands) 
	{
		SqliteUtilities::executeCommand(command);
	}
}

std::vector<SqliteCommand> SqliteUtilities::readFileCommands(SqliteFileCommands fileCommands)
{
	std::string fileContent = "";
	std::vector<std::string> queries;

	fileContent = FileUtilities::readFile(fileCommands.filePath);
	queries = StringUtilities::splitStringToVector(fileContent, DELIMITER);

	return SqliteUtilities::createCommandsVector(queries, fileCommands.settings);
}

std::vector<SqliteCommand> SqliteUtilities::createCommandsVector(std::vector<std::string> queries, CommandSettings settings)
{
	std::vector<SqliteCommand> commands;

	for (auto& query : queries)
	{
		commands.push_back(SqliteCommand{ query, settings });
	}
	return commands;
}

