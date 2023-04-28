#include "SqliteUtilities.h"
#include "FileUtilities.h"
#include "StringUtilities.h"


void SqliteUtilities::executeCommand(SqliteCommand command)
{
	int res = 0;
	char** errMessage = nullptr;

	res = sqlite3_exec(command.settings.db, command.query.c_str(), command.settings.collback, command.settings.data, errMessage);
	if (res != SQLITE_OK)
	{
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
<<<<<<< HEAD
	queries = StringUtilities::splitStringToVector(fileContent, DELIMITER);
=======
	queries = splitStringToVector(fileContent, DELIMITER);
>>>>>>> b5186508f34566a8cad3b6dce007c5e92fa8bcf3

	return 	SqliteUtilities::createCommandsVector(queries, fileCommands.settings);
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

