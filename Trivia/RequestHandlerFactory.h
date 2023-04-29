#pragma once
#include "IDatabase.h"


class RequestHandlerFactory 
{
public:
	RequestHandlerFactory(IDatabase* datbase);


private:
	IDatabase* _database;
};