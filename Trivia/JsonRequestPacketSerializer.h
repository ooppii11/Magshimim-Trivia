#pragma once
#pragma once
#include "Response.h"
#include "BufferDeserializer.hpp"

class Serializer
{
public:
	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);
};