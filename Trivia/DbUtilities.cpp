#include "DbUtilities.h"

void DbUtilities::executeCommand(sqlite3* db, std::string command, int(*collback)(void*, int, char**, char**), void* data)
{
	int res = 0;
	char** errMessage = nullptr;

	res = sqlite3_exec(db, command.c_str(), collback, data, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception("DB ERORR");
	}
}
