#pragma once
#include "SymmetriCrypto.h"

#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"

#include <iostream>

class AESCryptoAlgorithm : public SymmetriCrypto 
{
public:
	AESCryptoAlgorithm();
	AESCryptoAlgorithm(std::string keyString, std::string ivString);
	AESCryptoAlgorithm(std::map<std::string, std::string>& keyAndIv);
	virtual std::string encrypt(const std::string& message) override;
	virtual std::string decrypt(const std::string& cipher) override;

	virtual std::string base64Encode(const std::string& cipher) const override;
	virtual std::string base64Decode(const std::string& cipher) const override;

	virtual void setKey(std::map<std::string, std::string>& keyAndIv) override;
	virtual std::map<std::string, std::string> getKey() const;

private:
	CryptoPP::SecByteBlock _key;
	CryptoPP::SecByteBlock _iv;
};
