#include "BufferDeserializer.hpp"

unsigned int BufferDeserializer::getResponseCodeFromRequest(std::vector<char> data)
{
    return static_cast<unsigned int>(data[0]);
}

unsigned int BufferDeserializer::getResponseCodeFromRequest(std::string data)
{
    return static_cast<unsigned int>(data[0]);
}

unsigned int BufferDeserializer::getResponseCodeFromRequest(char* data)
{
    return static_cast<unsigned int>(data[0]);
}

std::string BufferDeserializer::getMessageFromRequest(std::vector<char> data)
{
    std::string strData(data.begin(), data.end());
    return getMessageFromRequest(strData);
}

std::string BufferDeserializer::getMessageFromRequest(std::string data)
{
    return data.substr(4);;
}

std::string BufferDeserializer::getMessageFromRequest(char* data)
{
    std::string strData = data;
    return getMessageFromRequest(strData);
}
