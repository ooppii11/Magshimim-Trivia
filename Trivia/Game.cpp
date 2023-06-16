#include "Game.h"
#include "LoggedUser.h"

Game::Game(int gameId, std::vector<std::string> players, std::vector<Question> questions) :
	_gameId(gameId), _questions(questions)
{
	for (int i = 0; i < players.size(); i++)
	{
		this->_players[LoggedUser(players[i])] = GameData(this->_questions[0]);
	}
}


Question Game::getQuestionForUser(LoggedUser user)
{
	return this->_players[user].currentQuestion;
}

void Game::submitAnswer(LoggedUser user, int answerId)
{
	GameData userData = this->_players[user];

	if (userData.currentQuestion.getCorrectAnswerId() == answerId) { userData.correctAnswerCount++; }
	else { userData.wrongAnswerCount++; }

	userData.currentQuestion = this->_questions[userData.correctAnswerCount + userData.wrongAnswerCount];
}

void Game::removePlayer(LoggedUser user)
{
	auto it = this->_players.find(user);
	if (it != this->_players.end()) {
		this->_players.erase(it);
	}
}

int Game::getGameId() const
{
	return this->_gameId;
}

