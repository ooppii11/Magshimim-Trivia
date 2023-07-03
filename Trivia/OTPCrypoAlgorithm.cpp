#include "OTPCrypoAlgorithm.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
OTPCrypoAlgorithm::OTPCrypoAlgorithm()
{
    this->generateKey();
}

OTPCrypoAlgorithm::OTPCrypoAlgorithm(std::string key)
{
    this->_key = key[0];
}

std::string OTPCrypoAlgorithm::encrypt(const std::string& message) const
{
    std::string cipher;
    for (auto& ch : message) 
    {
        cipher = ch xor this->_key;
    }
    return cipher;
}

std::string OTPCrypoAlgorithm::decrypt(const std::string& cipher) const
{
    std::string massage;
    for (auto& ch : cipher)
    {
        massage = ch xor this->_key;
    }
    return massage;
}

std::string OTPCrypoAlgorithm::base64Encode(const std::string& cipher) const
{
    return Base64::base64Encode(cipher);
}

std::string OTPCrypoAlgorithm::base64Decode(const std::string& cipher) const
{
    return Base64::base64Decode(cipher);
}

std::string OTPCrypoAlgorithm::getKey() const
{
    std::string key = "";
    key += this->_key;
    return key;
}

void OTPCrypoAlgorithm::generateKey()
{
    std::srand(std::time(nullptr));
    unsigned int first = std::rand();
    unsigned int secend = std::rand();
    this->_key = ((char)std::pow(first, secend) xor std::rand());
}
