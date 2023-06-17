#include "FileUtilities.h"
#include <fstream>

std::string FileUtilities::readFile(std::string filePath)
{
    std::string fileContent = "";
    std::string line = "";
    std::ifstream file(filePath);
    
    if (file.is_open())
    {
        while(file)
        {
            std::getline(file, line);
            fileContent +=  line + '\n';
            line = "";
        }
    }
    return fileContent;
}

bool FileUtilities::fileExsists(const std::string& filePath)
{
    if (FILE* file = fopen(filePath.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}
