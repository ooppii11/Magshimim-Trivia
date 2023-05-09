#include "JsonRequestPacketSerializer.h"
#include "json.hpp"
#include <fstream>

Buffer Serializer::serializeResponse(ErrorResponse response)
{
	Buffer temp;
	temp.header = ERROR_RESPONSE_CODE;
    temp.message = "{\"Error\": \"" + response.message + "\"}";
	return temp;
}

Buffer Serializer::serializeResponse(LoginResponse response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

Buffer Serializer::serializeResponse(SignupResponse response)
{
	Buffer temp;
	temp.header = response.status;
	temp.message = "";
	return temp;
}

//json.dump()
//json.to_string()
/*
Json::StyledWriter styledWriter;
Json::FastWriter fastWriter;
Json::Value newValue;
newValue["key"] = value;

styledWriter.write(newValue);
fastWriter.write(newValue);
*/
