#include "MyBase64.h"

std::string Base64::base64Encode(const std::string& cipher)
{
	std::string base64Encoded;
	CryptoPP::StringSource(cipher, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64Encoded)));
	return base64Encoded;
}

std::string Base64::base64Decode(const std::string& cipher)
{
	std::string base64Decoded;
	CryptoPP::StringSource(cipher, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(base64Decoded)));
	return base64Decoded;
}
