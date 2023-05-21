#include "QuizManager.h"

QuizManager::QuizManager(std::shared_ptr<IDatabase> db) : _database(db)
{
}

std::vector<std::pair<std::string, int>> QuizManager::getPublicCategories() const
{
	return this->_database->getPublicCategories();
}

std::vector<std::pair<std::string, int>> QuizManager::getPrivagteCategories(const std::string& username)
{
	return this->_database->getPrivagteCategories(username);
}

void QuizManager::addNewCategory(Category category, const std::string& username)
{
	this->_database->addNewCategory(category, username);
}

void QuizManager::addNewQuestion(const unsigned int categorieId, std::string username, Question question)
{
	this->_database->addNewQuestion(categorieId, username, question);
}

void QuizManager::deleteCategory(int categoryId, const std::string& username)
{
	return this->_database->deleteCategory(categoryId, username);
}

void QuizManager::deleteQuestion(int categoryId, const std::string& username, const std::string& question)
{
	return this->_database->deleteQuestion(categoryId, username, question);
}

std::vector<Question> QuizManager::getCategoryQuestions(const unsigned int categoryId, const std::string& username) const
{
	return this->_database->getCategoryQuestions(categoryId, username);
}
