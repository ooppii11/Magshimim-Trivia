#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> datbase) :
	_database(datbase), _loginManager(_database), _roomManager(), _statisticsManager(_database), _quizManager(_database), _historyManager(_database), _gameManager(_database) {}


std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::shared_ptr<LoginRequestHandler>(new LoginRequestHandler(this->_loginManager, *this));
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->_statisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->_roomManager;
}

std::shared_ptr<RoomAdminRequestHandler> RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{	
	return std::shared_ptr<RoomAdminRequestHandler>(new RoomAdminRequestHandler(room, user, this->_roomManager, this->_loginManager, *this));
}

std::shared_ptr<RoomMemberRequestHandler> RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	return std::shared_ptr<RoomMemberRequestHandler>(new RoomMemberRequestHandler(room, user, this->_roomManager, this->_loginManager, *this));
}


std::shared_ptr<GameRequestHandler> RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game game)
{
	return std::shared_ptr<GameRequestHandler>(new GameRequestHandler(user, game, this->_gameManager, *this));
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->_gameManager;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->_loginManager;
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return std::shared_ptr<MenuRequestHandler>(new MenuRequestHandler(user, this->_historyManager,this->_roomManager, this->_statisticsManager, *this, this->_quizManager, this->_loginManager));
}
