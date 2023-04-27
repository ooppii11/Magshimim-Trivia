#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>


class DbUtilities
{
public:
	static void executeCommand(sqlite3* db, std::string command, int(*collback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
};