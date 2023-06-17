#pragma once
#include "Question.h"
#include <map>
#include <vector>
#include "LoggedUser.h"
#include "Response.h"


struct GameData
{
    GameData(const Question& question, unsigned int correctCount, unsigned int wrongCount, float avgTime)
        : currentQuestion(question), correctAnswerCount(correctCount),
        wrongAnswerCount(wrongCount), averageAnswerTime(avgTime)
    {}

    Question currentQuestion;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    float averageAnswerTime;
};

struct PlayerResultsComparator
{
	bool operator()(const  PlayerResults& a, const  PlayerResults& b)
	{
		if (a.correctAnswerCount == b.correctAnswerCount)
		{
			return a.averageAnswerTime < b.averageAnswerTime;
		}
		return a.correctAnswerCount > b.correctAnswerCount;
	}
};


class Game
{
public:
	Game(unsigned int gameId, std::vector<std::string> players, std::vector<Question> questions);

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, int answerId);
	void removePlayer(LoggedUser user);

	int getNumberOfPslyers() const;
	int getGameId() const;

	std::vector <PlayerResults> getPalyersResults();

private:
	std::vector<Question> _questions;
	std::map<std::string, GameData>  _players;
	unsigned int _gameId;
	int _numOfPlayers;

};
