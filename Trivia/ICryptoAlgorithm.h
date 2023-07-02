#pragma once
#include <string>

class ICryptoAlgorithm 
{
public:
	virtual std::string encrypt(std::string key) = 0;
	virtual std::string decrypt(std::string key) = 0;
};