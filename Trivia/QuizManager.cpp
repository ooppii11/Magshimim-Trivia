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

std::vector<Question> QuizManager::getCategoryQuestions(const unsigned int categorieId) const
{
	return this->_database->getCategoryQuestions(categorieId);
}