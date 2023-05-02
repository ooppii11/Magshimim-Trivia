#include "RequestHandlerFactory.h"

<<<<<<< HEAD
RequestHandlerFactory::RequestHandlerFactory(IDatabase* datbase):
	_database(datbase) {}
=======
RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<IDatabase> datbase) :
	_database(datbase), _loginManager(_database){}

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
	return std::shared_ptr<MenuRequestHandler>(new MenuRequestHandler());
}
>>>>>>> 04817e37b87cb63292ba68643c5fb6aa681d2807
