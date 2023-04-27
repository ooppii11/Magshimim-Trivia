#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>


typedef struct DbCommand
{
	sqlite3* db;
	std::string command;
	int(*collback)(void*, int, char**, char**) = nullptr;
	void* data = nullptr;
}DbCommand;

class DbUtilities
{
public:
	static void executeCommand(DbCommand command);
};