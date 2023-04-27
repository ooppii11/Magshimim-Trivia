#include "DbUtilities.h"

void DbUtilities::executeCommand(DbCommand command)
{
	int res = 0;
	char** errMessage = nullptr;

	res = sqlite3_exec(command.db, command.command.c_str(), command.collback, command.data, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception("DB ERORR");
	}
}
