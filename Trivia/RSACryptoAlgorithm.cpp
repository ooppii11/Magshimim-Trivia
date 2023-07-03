#include "RSACryptoAlgorithm.h"

RSACryptoAlgorithm::RSACryptoAlgorithm()
{
	this->_params.GenerateRandomWithKeySize(this->_rng, KEYS_SIZE);
}

std::string RSACryptoAlgorithm::encrypt(const std::string& message) const
{
	std::string cipher;
	CryptoPP::RSA::PublicKey publicKey(this->_params);
	CryptoPP::RSAES_OAEP_SHA_Encryptor e(publicKey);
	CryptoPP::StringSource(message, true, new CryptoPP::PK_EncryptorFilter(this->_rng, e, new CryptoPP::StringSink(cipher)));
	return cipher;
}

std::string RSACryptoAlgorithm::decrypt(const std::string& cipher) const
{
	std::string recovered;
	CryptoPP::RSA::PrivateKey privateKey(this->_params);
	CryptoPP::RSAES_OAEP_SHA_Decryptor d(privateKey);
	CryptoPP::StringSource(cipher, true, new CryptoPP::PK_DecryptorFilter(this->_rng, d, new CryptoPP::StringSink(recovered)));
	return recovered;

}

std::string RSACryptoAlgorithm::base64Encode(const std::string& cipher) const
{
	return Base64::base64Encode(cipher);
}

std::string RSACryptoAlgorithm::base64Decode(const std::string& cipher) const
{
	return Base64::base64Decode(cipher);
}


std::string RSACryptoAlgorithm::getKey() const
{
	CryptoPP::RSA::PublicKey publicKey(this->_params);
	std::string encodedPublicKey;
	CryptoPP::StringSink stringSink(encodedPublicKey);
	publicKey.Save(stringSink);

	return encodedPublicKey;
}
