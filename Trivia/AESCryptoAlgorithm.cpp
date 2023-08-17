#include "AESCryptoAlgorithm.h"

AESCryptoAlgorithm::AESCryptoAlgorithm() : _key(CryptoPP::AES::DEFAULT_KEYLENGTH), _iv(CryptoPP::AES::BLOCKSIZE)
{
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(this->_key, this->_key.size());
    prng.GenerateBlock(this->_iv, this->_iv.size());

}
AESCryptoAlgorithm::AESCryptoAlgorithm(std::string keyString, std::string ivString)
{
    this->_key.Assign(reinterpret_cast<const CryptoPP::byte*>(keyString.data()), keyString.size());
    this->_iv.Assign(reinterpret_cast<const CryptoPP::byte*>(ivString.data()), ivString.size());
}

AESCryptoAlgorithm::AESCryptoAlgorithm(std::map<std::string, std::string>& keyAndIv)
{
    this->_key.Assign(reinterpret_cast<const CryptoPP::byte*>(keyAndIv["Key"].data()), keyAndIv["Key"].size());
    this->_iv.Assign(reinterpret_cast<const CryptoPP::byte*>(keyAndIv["Iv"].data()), keyAndIv["Iv"].size());
}

std::string AESCryptoAlgorithm::encrypt(const std::string& message)
{
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(this->_key, this->_key.size(), this->_iv);
        std::string cipher;

        CryptoPP::StringSource s(message, true,
            new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(cipher)
            )
        );
        return cipher;
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        //throw std::exception
    }
}

std::string AESCryptoAlgorithm::decrypt(const std::string& cipher)
{
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(this->_key, this->_key.size(), this->_iv);
        std::string recovered;

        CryptoPP::StringSource s(cipher, true,
            new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recovered)
            )
        );
        return recovered;
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        //throw std::exception
    }
}

std::string AESCryptoAlgorithm::base64Encode(const std::string& cipher) const
{
    return Base64::base64Encode(cipher);
}

std::string AESCryptoAlgorithm::base64Decode(const std::string& cipher) const
{
    return Base64::base64Decode(cipher);
}

void AESCryptoAlgorithm::setKey(std::map<std::string, std::string>& keyAndIv)
{
    this->_key.Assign(reinterpret_cast<const CryptoPP::byte*>(keyAndIv["Key"].data()), keyAndIv["Key"].size());
    this->_iv.Assign(reinterpret_cast<const CryptoPP::byte*>(keyAndIv["Iv"].data()), keyAndIv["Iv"].size());
}

std::map<std::string, std::string> AESCryptoAlgorithm::getKey() const
{
    std::map<std::string, std::string> keyAndIv;
    keyAndIv["Key"] = this->base64Encode(std::string(reinterpret_cast<const char*>(this->_key.data()), this->_key.size()));
    keyAndIv["Iv"] = this->base64Encode(std::string(reinterpret_cast<const char*>(this->_iv.data()), this->_iv.size()));
    return keyAndIv;
}