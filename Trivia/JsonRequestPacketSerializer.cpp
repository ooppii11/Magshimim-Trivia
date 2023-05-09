#include "JsonRequestPacketSerializer.h"
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

//json.dump()
/*
Json::StyledWriter styledWriter;
Json::FastWriter fastWriter;
Json::Value newValue;
newValue["key"] = value;

styledWriter.write(newValue);
fastWriter.write(newValue);
*/


//vector to string:
/*
std::vector<int> vec { 6, 3, 8, -9, 1, -2, 8 };
//in order to get the type of the vector: using T = typename std::decay<decltype(*vec.begin())>::type;
std::stringstream ss;
ss << "[";
std::ostringstream oss;
if (!vec.empty())
{
	std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(oss, ", "));
	oss << vec.back();
}
ss << "]";
return ss.str();
*/


Buffer Serializer::serializeResponse(ErrorResponse response)
{
	Buffer temp;
	json data;
	data["Error"] = response.message;
	temp.header = ERROR_RESPONSE_CODE;
    temp.message = data.dump();
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

