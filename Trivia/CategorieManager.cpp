#include "CategorieManager.h"

CategorieManager::CategorieManager(std::shared_ptr<IDatabase> db, std::string username) : _database(db), _username(username)
{
}

std::vector<std::pair<std::string, int>> CategorieManager::getPublicCategories() const
{
    return this->_database->getPublicCategories();
}

std::vector<std::pair<std::string, int>> CategorieManager::getPrivagteCategories(const std::string& username)
{
    return this->_database->getPrivagteCategories(this->_username);
}
