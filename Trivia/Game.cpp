#include "Game.h"

Game::Game(int gameId, std::map<LoggedUser, GameData> players, std::vector<Question> questions) :
	_gameId(gameId), _players(players), _questions(questions) {}


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
