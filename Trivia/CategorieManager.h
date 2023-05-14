#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IDatabase.h"
typedef unsigned int roomID;

class CategorieManager
{
public:
	CategorieManager(std::shared_ptr<IDatabase> db, std::string username);
	std::vector<std::pair<std::string, int>> getPublicCategories() const;
	std::vector<std::pair<std::string, int>> getPrivagteCategories(const std::string& username);

private:
	std::shared_ptr<IDatabase> _database;
	std::string _username;
};