#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> datbase) :
	_database(datbase), _loginManager(_database), _roomManager(), _statisticsManager(_database), _categoriesManager(_database) {}

std::shared_ptr<LoginRequestHandler> RequestHandlerFactory::createLoginRequestHandler()
{
	return std::shared_ptr<LoginRequestHandler>(new LoginRequestHandler(this->_loginManager, *this));
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->_loginManager;
}

std::shared_ptr<MenuRequestHandler> RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return std::shared_ptr<MenuRequestHandler>(new MenuRequestHandler(user, this->_roomManager, this->_statisticsManager, *this, this->_categoriesManager));
}
