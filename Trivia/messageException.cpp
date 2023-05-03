#include "messageException.h"

messageException::messageException(std::string error)
{
	this->_returnedException = new char[error.length() + 1];
	strcpy(this->_returnedException, error.c_str());
}

messageException::~messageException()
{
	delete this->_returnedException;
}

const char* messageException::what() const
{
	return this->_returnedException;
}
