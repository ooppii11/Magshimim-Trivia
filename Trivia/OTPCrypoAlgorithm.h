#pragma once
#include "ICryptoAlgorithm.h"


class OTPCrypoAlgorithm : public ICryptoAlgorithm
{
public:
	virtual std::string encrypt(std::string message) override;
	virtual std::string decrypt(std::string cipher) override;
	
private:
	unsigned char _key;

	unsigned char generateKey();



};	