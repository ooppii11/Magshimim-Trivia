#pragma once
#include <string>

class ICryptoAlgorithm 
{
public:
	virtual std::string encrypt(std::string message) = 0;
	virtual std::string decrypt(std::string cipher) = 0;
};