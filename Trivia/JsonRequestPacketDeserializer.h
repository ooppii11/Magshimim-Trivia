#pragma once
#include "Request.h"
#include "BufferDeserializer.hpp"

class Deserializer
{
public:
	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
	
};