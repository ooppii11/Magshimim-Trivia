#pragma once
#include <string>

class FileUtilities
{
public:
	static std::string readFile(std::string filePath);
	static bool fileExsists(const std::string& filePath);
};