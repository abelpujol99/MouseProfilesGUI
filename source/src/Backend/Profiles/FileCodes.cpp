#include "Backend/Profile/FileCodes.h"

FileCodes::FileCodes(std::string&& filePath, std::unordered_set<Code>&& codes)
    : _filePath(std::move(filePath)), _codes(std::move(codes)) {
}

std::string FileCodes::GetFilePath()
{
    return _filePath;
}

std::unordered_set<Code> FileCodes::GetCodes()
{
    return _codes;
}
