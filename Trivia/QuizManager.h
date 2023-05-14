#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IDatabase.h"

class QuizManager
{
public:
	QuizManager(std::shared_ptr<IDatabase> db);
	std::vector<std::pair<std::string, int>> getPublicCategories() const;
	std::vector<std::pair<std::string, int>> getPrivagteCategories(const std::string& username);
	void addNewCategory(Category category, const std::string& username);
	void addNewQuestion(const unsigned int categorieId, std::string  username, Question question);
	std::vector<Question> getCategoryQuestions(const unsigned int categorieId) const;

private:
	std::shared_ptr<IDatabase> _database;
};