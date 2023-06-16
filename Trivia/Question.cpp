#include "Question.h"

Question::Question(QuestionStruct question)
{
	this->_question = question.question;
	this->_correcteAnswerIndex = question.correctAnswerIndex;
	this->_possibleAnswers.push_back(question.firstAnswer);
	this->_possibleAnswers.push_back(question.secondAnswer);
	this->_possibleAnswers.push_back(question.thirdAnswer);
	this->_possibleAnswers.push_back(question.fourthAnswer);
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


