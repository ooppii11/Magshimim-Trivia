#pragma once
#include "cryptlib.h"
//#include "rijndael.h"
#include "modes.h"
#include "rsa.h"
#include "sha.h"
//#include "files.h"
#include "osrng.h"
#include "hex.h"

#include "ICryptoAlgorithm.h"

#define KEYS_SIZE CryptoPP::RSA::DEFAULT_KEYLENGTH

class RSACryptoAlgorithm : public ICryptoAlgorithm
{
public:
	RSACryptoAlgorithm();
	virtual std::string encrypt(std::string message) override; 
	virtual std::string decrypt(std::string message) override;

private:
	CryptoPP::AutoSeededRandomPool _rng;
	CryptoPP::InvertibleRSAFunction _params;
}; 