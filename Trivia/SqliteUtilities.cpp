#include "SqliteUtilities.h"

void SqliteUtilities::executeCommand(SqliteCommand command)
{
	int res = 0;
	char** errMessage = nullptr;

	res = sqlite3_exec(command.db, command.query.c_str(), command.collback, command.data, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception("DB ERORR");
	}
}

void SqliteUtilities::executeCommands(std::vector<SqliteCommand> commands)
{
	for (auto& command : commands) 
	{
		SqliteUtilities::executeCommand(command);
	}
}

