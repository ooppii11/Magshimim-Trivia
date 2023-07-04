#pragma once
#include "cryptlib.h"
#include "modes.h"
#include "rsa.h"
#include "sha.h"
#include "osrng.h"
#include "hex.h"
#include "base64.h"

#include "AsymmetriCrypto.h"
#include "MyBase64.h"

#define KEYS_SIZE 2048
//3072

class RSACryptoAlgorithm : public AsymmetriCrypto
{
public:
	RSACryptoAlgorithm();
	virtual std::string encrypt(const std::string& message) override;
	virtual std::string decrypt(const std::string& cipher) override;

	virtual std::string base64Encode(const std::string& cipher) const override;
	virtual std::string base64Decode(const std::string& cipher) const override;

	virtual std::map<std::string, std::string> getKey() const override;

private:
	CryptoPP::AutoSeededRandomPool _rng;
	CryptoPP::InvertibleRSAFunction _params;
}; 