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

std::map<unsigned int, std::string> Question::getPossibleAnswers()
{
	std::map<unsigned int, std::string> answers;

	for (int i = 0; i < this->_possibleAnswers.size(); i++)
	{
		answers[i] = this->_possibleAnswers[i];
	}
	return answers;
}

int Question::getCorrectAnswerId()
{
	return this->_correcteAnswerIndex;
}

bool Question::operator==(const Question& question)
{
	return this->_question == question._question;
}

