#pragma once
#include "Question.h"
#include <map>
#include <vector>
#include "LoggedUser.h"


typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averangeAnswerTime;


	GameData(Question current) : correctAnswerCount(0), wrongAnswerCount(0), averangeAnswerTime(0), currentQuestion(current) {}
} GameData;

class Game
{
public:
	Game(int gameId, std::vector<std::string> players, std::vector<Question> questions);

	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, int answerId);
	void removePlayer(LoggedUser user);

	int getGameId() const;

private:
	std::vector<Question> _questions;
	std::map<LoggedUser, GameData>  _players;
	int _gameId;
};
