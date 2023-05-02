#pragma once
#include "Request.h"
#include "BufferDeserializer.hpp"

class Deserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);
};