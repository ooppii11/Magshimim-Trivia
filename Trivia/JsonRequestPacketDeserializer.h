#pragma once
#include "Request.h"
#include "BufferDeserializer.hpp"

namespace Deserializer
{
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);
}