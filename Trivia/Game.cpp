#include "Game.h"
#include "LoggedUser.h"

Game::Game(unsigned int gameId, std::vector<std::string> players, std::vector<Question> questions) :
	_gameId(gameId), _questions(questions)
{
	for (int i = 0; i < players.size(); i++)
	{
		GameData userData = { questions[0], 0, 0, 0.0};
		this->_players.insert(std::make_pair(players[i], userData));
	}
}


Question Game::getQuestionForUser(LoggedUser user)
{	
	auto it = this->_players.find(user.getUsername());
	if (it != this->_players.end())
	{
		return it->second.currentQuestion;
	}
	else
	{
		throw std::exception("User not found.");
	}
}

void Game::submitAnswer(LoggedUser user, int answerId)
{
	GameData& userData = this->_players.at(user.getUsername());
	
	if (userData.currentQuestion.getCorrectAnswerId() == answerId) { userData.correctAnswerCount++; }
	else { userData.wrongAnswerCount++; }

	if (userData.correctAnswerCount + userData.wrongAnswerCount < this->_questions.size())
	{
		userData.currentQuestion = this->_questions[userData.correctAnswerCount + userData.wrongAnswerCount];
	}
	else
	{
		throw (std::exception("Game end"));
	}
}

void Game::removePlayer(LoggedUser user)
{
	auto it = this->_players.find(user.getUsername());
	if (it != this->_players.end()) {
		this->_players.erase(it);
	}
}

int Game::getGameId() const
{
	return this->_gameId;
}

