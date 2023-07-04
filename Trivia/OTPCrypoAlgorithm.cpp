#include "OTPCrypoAlgorithm.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

std::string OTPCrypoAlgorithm::encrypt(const std::string& message)
{
    std::string cipher;
    this->generateKey(message.size());
    int i = 0;
    for (i = 0; i < message.size(); i++) 
    {
        cipher += message[i] xor this->_key[i];
    }
    return cipher;
}

std::string OTPCrypoAlgorithm::decrypt(const std::string& cipher)
{
    std::string message;
    int i = 0;
    for (i = 0; i < cipher.size(); i++)
    {
        message += cipher[i] xor this->_key[i];
    }
    return message;
}

std::string OTPCrypoAlgorithm::base64Encode(const std::string& cipher) const
{
    return Base64::base64Encode(cipher);
}

std::string OTPCrypoAlgorithm::base64Decode(const std::string& cipher) const
{
    return Base64::base64Decode(cipher);
}

void OTPCrypoAlgorithm::setKey(std::map<std::string, std::string>& key)
{
    this->_key = key["Key"];
}

std::map<std::string, std::string> OTPCrypoAlgorithm::getKey() const
{
    std::map<std::string, std::string> key;
    key["Key"] = this->_key;
    return key;
}

void OTPCrypoAlgorithm::generateKey(int size)
{
    int i = 0;
    this->_key = "";
    for (i = 0; i < size; size++)
    {
        std::srand(std::time(nullptr));
        unsigned int first = std::rand();
        unsigned int secend = std::rand();
        this->_key += ((unsigned char)std::pow(first, secend) xor std::rand());
    }
}
    