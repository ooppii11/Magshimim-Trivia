#include "StringUtilities.h"

std::vector<std::string> StringUtilities::splitStringToVector(std::string string, std::string delimiter)
{
    int postion = 0;
    std::vector<std::string> strings;
    
    while ((postion = string.find(delimiter)) != std::string::npos)
    {
        strings.push_back(string.substr(0, postion));
        string.erase(0, postion + delimiter.length());
    }
    
    return strings;
}
