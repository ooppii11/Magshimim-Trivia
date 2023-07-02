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
	virtual std::string decrypt(std::string message) override;

private:
	CryptoPP::HexEncoder encoder;//new CryptoPP::FileSink(std::cout)
	CryptoPP::SecByteBlock key; //CryptoPP::AES::DEFAULT_KEYLENGTH
	CryptoPP::SecByteBlock iv; //CryptoPP::AES::BLOCKSIZE
};