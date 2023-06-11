#pragma once
#include <string>
#include <vector>


class Question 
{
public:
	Question(std::string question, std::vector<std::string> possibleAnswers, int correcteAnswerIndex);

	std::string getQuestion();
	std::vector<std::string>  getPossibleAnswers();
	int getCorrectAnswerId();

private:
	int _correcteAnswerIndex;
	std::string _question;
	std::vector<std::string> _possibleAnswers;
};