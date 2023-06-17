#include "Game.h"
#include "LoggedUser.h"

Game::Game(unsigned int gameId, std::vector<std::string> players, std::vector<Question> questions, float maxTimePerQuestion) :
	_gameId(gameId), _questions(questions), _numOfPlayers(players.size()), _maxTimePerQuestion(maxTimePerQuestion)
{
	this->startTime = std::chrono::system_clock::now();
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
	auto it = find(this->_questions.begin(), this->_questions.end(), userData.currentQuestion);
	int numOfQuestion = it - this->_questions.begin();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->startTime).count();
	if (duration > this->_maxTimePerQuestion * numOfQuestion + TIME_OF_RECEIVING_AN_ANSWER * (numOfQuestion - 1))
	{
		throw std::exception("Time pass");
	}

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
	this->_numOfPlayers--;
}

int Game::getNumberOfPslyers() const
{
	return this->_numOfPlayers;
}

int Game::getGameId() const
{
	return this->_gameId;
}

std::vector<PlayerResults> Game::getPalyersResults()
{
	std::vector<PlayerResults> results;

	for (auto it : this->_players)
	{
		PlayerResults playerResults;

		playerResults.username = it.first;
		playerResults.averageAnswerTime = it.second.averageAnswerTime;
		playerResults.correctAnswerCount = it.second.correctAnswerCount;
		playerResults.wrongAnswerCount = it.second.wrongAnswerCount;

		results.push_back(playerResults);
	}
	std::sort(results.begin(), results.end(), PlayerResultsComparator());

	return results;
}

