#pragma once
#include "SymmetriCrypto.h"


class OTPCrypoAlgorithm : public SymmetriCrypto
{
public:
	virtual std::string encrypt(const std::string& message) override;
	virtual std::string decrypt(const std::string& cipher) override;

	virtual std::string base64Encode(const std::string& cipher) const override;
	virtual std::string base64Decode(const std::string& cipher) const override;

	virtual void setKey(std::map<std::string, std::string>& key) override;
	virtual std::map<std::string, std::string> getKey() const override;
	
private:
	std::string _key;

	void generateKey(int size);



};	