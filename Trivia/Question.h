#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"

typedef struct QuestionStruct
{
	std::string question;
	int correctAnswerIndex;
	std::string firstAnswer;
	std::string secondAnswer;
	std::string thirdAnswer;
	std::string fourthAnswer;


} QuestionStruct;


class Question
{
public:
	Question(QuestionStruct question);

	std::string getQuestion();
	std::vector<std::string>  getPossibleAnswers();
	int getCorrectAnswerId();

private:
	int _correcteAnswerIndex;
	std::string _question;
	std::vector<std::string> _possibleAnswers;
};
