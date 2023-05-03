#pragma once
#include <exception>
#include <string>
#include <memory>

class messageException : public std::exception
{
public:
	messageException(std::string error);
	~messageException();
	virtual const char* what() const;

private:
	char* _returnedException;

};