#pragma once
#include <exception>
#include <string>

class messageException : public std::exception
{
public:
	messageException(std::string error);
	~messageException();
	virtual const char* what() const;

private:
	char* _returnedException;

};