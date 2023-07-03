#pragma once
#include "SymmetriCrypto.h"


class OTPCrypoAlgorithm : public SymmetriCrypto
{
public:
	OTPCrypoAlgorithm();
	OTPCrypoAlgorithm(std::string key);
	virtual std::string encrypt(const std::string& message) const override;
	virtual std::string decrypt(const std::string& cipher) const override;

	virtual std::string base64Encode(const std::string& cipher) const override;
	virtual std::string base64Decode(const std::string& cipher) const override;

	//virtual void setKey(std::string& key) override;
	virtual std::string getKey() const override;
	
private:
	unsigned char _key;

	void generateKey();



};	