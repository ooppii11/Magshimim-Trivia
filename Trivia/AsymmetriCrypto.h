#pragma once
#include "ICryptoAlgorithm.h"

class AsymmetriCrypto : public ICryptoAlgorithm
{
	virtual std::string encrypt(const std::string& message) const = 0;
	virtual std::string decrypt(const std::string& cipher) const = 0;
	//virtual void setKey(std::string key) = 0;
	virtual std::string getKey() const = 0;
	virtual std::string base64Encode(const std::string& cipher) const = 0;
	virtual std::string base64Decode(const std::string& cipher) const = 0;
};