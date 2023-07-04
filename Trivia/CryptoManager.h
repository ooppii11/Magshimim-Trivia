#pragma once
#include "RSACryptoAlgorithm.h"
#include "AESCryptoAlgorithm.h"
#include <WinSock2.h>
#include <Windows.h>
#include <memory>

#define MESSAGE_HEADR_SIZE 4

class CryptoManager 
{
public:
	CryptoManager();
	void exchangeKeys(SOCKET clientSocket);
	std::string encrypt(const std::string& message);
	std::string decrypt(const std::string& cipher);
private:
	std::shared_ptr<AsymmetriCrypto> _transferKeys;
	std::shared_ptr<SymmetriCrypto> _encryption_decryptionkey;

	std::string recvKey(SOCKET clientSocket, const unsigned int bytesNum = 16);
	std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);
	void sendKey(SOCKET clientSocket, std::string key);


};