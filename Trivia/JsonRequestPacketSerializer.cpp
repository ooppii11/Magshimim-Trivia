#include "JsonRequestPacketSerializer.h"

Buffer Serializer::serializeResponse(ErrorResponse response)
{
	Buffer temp;
	temp.header = 99;
    temp.message = "{\"Error\": \"" + response.message + "\"}";
	return temp;
}

Buffer Serializer::serializeResponse(LoginResponse response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "{}";
	return temp;
}

Buffer Serializer::serializeResponse(SignupResponse response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "{}";
	return temp;
}
