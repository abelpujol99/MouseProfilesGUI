#pragma once

#include <string>
#include <unordered_set>

#include "../../../shared/usings/CodeUsings.h"

class FileCodes
{
public:

    FileCodes(std::string&& filePath, std::unordered_set<Code>&& codes);

    std::string GetFilePath();
    std::unordered_set<Code> GetCodes();

private:
    std::string _filePath;
    std::unordered_set<Code> _codes;

};