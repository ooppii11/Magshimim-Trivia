#pragma once
#include "base64.h"
#include "cryptlib.h"
#include "osrng.h"

#include <string>

class Base64 
{
public :
	static std::string base64Encode(const std::string& cipher);
	static std::string base64Decode(const std::string& cipher);
	
};