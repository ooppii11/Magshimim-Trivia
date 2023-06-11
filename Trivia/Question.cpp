#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, int correcteAnswerIndex)
{
	this->_question = question;
	this->_correcteAnswerIndex = correcteAnswerIndex;
	this->_possibleAnswers;
}

std::string Question::getQuestion()
{
	return this->_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return this->_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
	return this->_correcteAnswerIndex;
}
