#include "AESCryptoAlgorithm.h"

AESCryptoAlgorithm::AESCryptoAlgorithm() : _encoder(new CryptoPP::FileSink(std::cout)), _key(CryptoPP::AES::DEFAULT_KEYLENGTH), _iv(CryptoPP::AES::BLOCKSIZE)
{
	CryptoPP::AutoSeededRandomPool prng;
	prng.GenerateBlock(this->_key, this->_key.size());
	prng.GenerateBlock(this->_iv, this->_iv.size());

}

std::string AESCryptoAlgorithm::encrypt(std::string message)
{
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
        e.SetKeyWithIV(this->_key, this->_key.size(), this->_iv);
        std::string cipher;

        CryptoPP::StringSource s(message, true,
            new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
        return cipher;
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

std::string AESCryptoAlgorithm::decrypt(std::string cipher)
{
    try
    {
        CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
        d.SetKeyWithIV(this->_key, this->_key.size(), this->_iv);
        std::string recovered;

        CryptoPP::StringSource s(cipher, true,
            new CryptoPP::StreamTransformationFilter(d,
                new CryptoPP::StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource

        return recovered;
    }
    catch (const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
