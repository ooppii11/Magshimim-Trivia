#pragma once
#include <vector>
#include <memory>
#include <string>
#include "IDatabase.h"

class QuizManager
{
public:
	QuizManager(std::shared_ptr<IDatabase> db);

	std::map<int, std::string> getPublicCategories() const;
	std::map<int, std::string> getPrivagteCategories(const std::string& username);
	std::vector<Question> getCategoryQuestions(const unsigned int categorieId, const std::string& username) const;

	void addNewCategory(Category category, const std::string& username);
	void addNewQuestion(const unsigned int categorieId, std::string  username, QuestionStruct question);

	void deleteCategory(int categoryId, const std::string& username);
	void deleteQuestion(int categoryId, const std::string& username, const std::string& question);

private:
	std::shared_ptr<IDatabase> _database;
};