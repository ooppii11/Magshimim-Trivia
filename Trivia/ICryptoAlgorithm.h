#pragma once
#include <string>
#include <map>
#include "MyBase64.h"

class ICryptoAlgorithm 
{
public:
	virtual std::string encrypt(const std::string& message) = 0;
	virtual std::string decrypt(const std::string& cipher) = 0;
	//virtual void setKey(std::string key) = 0;
	virtual std::map<std::string, std::string> getKey() const = 0;
	virtual std::string base64Encode(const std::string& cipher) const = 0;
	virtual std::string base64Decode(const std::string& cipher) const = 0;
};