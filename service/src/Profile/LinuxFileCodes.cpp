#include "Profile/LinuxFileCodes.h"

LinuxFileCodes::LinuxFileCodes(std::string&& filePath, std::unordered_set<Code>&& codes)
    : _filePath(std::move(filePath)), _codes(std::move(codes)) {
}

std::string LinuxFileCodes::GetFilePath()
{
    return _filePath;
}

std::unordered_set<Code> LinuxFileCodes::GetCodes()
{
    return _codes;
}
