#pragma once
#include <string>
#include <vector>

typedef struct Buffer
{
	unsigned int header;
	std::string message;
}Buffer;

namespace BufferDeserializer
{
	static unsigned int getResponseCodeFromRequest(std::vector<char> data);
	static unsigned int getResponseCodeFromRequest(std::string data);
	static unsigned int getResponseCodeFromRequest(char* data);

	static std::string getMessageFromRequest(std::vector<char> data);
	static std::string getMessageFromRequest(std::string data);
	static std::string getMessageFromRequest(char* data);

	template <class T>
	static Buffer buildBuffer(T data)
	{
		Buffer temp;
		temp.header = getResponseCodeFromRequest(data);
		temp.message = getMessageFromRequest(data);
		return temp;
	}
}