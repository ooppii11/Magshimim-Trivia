#include "CryptoManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonRequestPacketSerializer.hpp"
#include "BufferDeserializer.hpp"

CryptoManager::CryptoManager() : _transferKeys(new RSACryptoAlgorithm()), _encryption_decryptionkey(new AESCryptoAlgorithm())
{
}

void CryptoManager::exchangeKeys(SOCKET clientSocket)
{
	PublicKey key;
	Buffer data;
	key.key = this->_transferKeys->getKey();
	data = Serializer::serializeResponse(key);
	this->sendKey(clientSocket, this->_transferKeys->base64Encode(data.message));
	data.message = this->recvKey(clientSocket);
	data.message = this->_transferKeys->base64Decode(data.message);
	std::map<std::string, std::string> userKey = Deserializer::deserializeSubminUserKey(data).key;
	userKey["Key"] = this->_transferKeys->decrypt(this->_transferKeys->base64Decode(userKey["Key"]));
	userKey["Iv"] = this->_transferKeys->decrypt(this->_transferKeys->base64Decode(userKey["Iv"]));
	this->_encryption_decryptionkey->setKey(userKey);
}

std::string CryptoManager::encrypt(const std::string& message)
{
    return this->_encryption_decryptionkey->base64Encode(this->_encryption_decryptionkey->encrypt(message));
}

std::string CryptoManager::decrypt(const std::string& cipher)
{
    return this->_encryption_decryptionkey->decrypt(this->_encryption_decryptionkey->base64Decode(cipher));
}

std::string CryptoManager::recvKey(SOCKET clientSocket, const unsigned int bytesNum)
{
	std::string buff = "";
	std::string meg = "";
	do
	{
		buff = getPartFromSocket(clientSocket, bytesNum, 0);
		buff.erase(std::remove(buff.begin(), buff.end(), -51), buff.end());
		meg += buff;
	} while (buff != "");

	return meg;
}

std::string CryptoManager::getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::cout << WSAGetLastError() << std::endl;
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		delete[] data;
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);

	delete[] data;
	return received;
}

void CryptoManager::sendKey(SOCKET clientSocket, std::string key)
{
	char* buffer = nullptr;
	buffer = new char[key.size() + 1];
	memcpy(buffer, key.c_str(), key.size());
	send(clientSocket, buffer, key.size(), 0);
	delete[] buffer;
}