#pragma once
#pragma once
#include "Response.h"
#include "BufferDeserializer.hpp"

namespace Serializer
{
	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);
}