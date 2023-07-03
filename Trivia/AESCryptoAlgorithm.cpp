#include "AESCryptoAlgorithm.h"

AESCryptoAlgorithm::AESCryptoAlgorithm() : _key(CryptoPP::AES::DEFAULT_KEYLENGTH), _iv(CryptoPP::AES::BLOCKSIZE)
{
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(this->_key, this->_key.size());
    prng.GenerateBlock(this->_iv, this->_iv.size());

}
AESCryptoAlgorithm::AESCryptoAlgorithm(std::string keyString, std::string ivString)
{
    CryptoPP::AutoSeededRandomPool prng;
    this->_key.Assign((const CryptoPP::byte*)keyString.data(), keyString.size());
    this->_iv.Assign((const CryptoPP::byte*)ivString.data(), ivString.size());
}

std::string AESCryptoAlgorithm::encrypt(const std::string& message) const
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

std::string AESCryptoAlgorithm::decrypt(const std::string& cipher) const
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

std::string AESCryptoAlgorithm::getKey() const
{
    return std::string(reinterpret_cast<const char*>(this->_key.data()), this->_key.size());
}

std::string AESCryptoAlgorithm::getIv() const
{
    return std::string(reinterpret_cast<const char*>(this->_iv.data()), this->_iv.size());
}
