#pragma once
#include "ICryptoAlgorithm.h"
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>

class AESCryptoAlgorithm : public ICryptoAlgorithm
{
public:
	AESCryptoAlgorithm();
	virtual std::string encrypt(std::string message) override;
	virtual std::string decrypt(std::string cipher) override;

private:
	CryptoPP::HexEncoder _encoder;
	CryptoPP::SecByteBlock _key;
	CryptoPP::SecByteBlock _iv;
};