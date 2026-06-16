#pragma once
#include <string>

struct DeviceInfo
{
    std::vector<std::string> path;
    std::string name;
};

inline bool operator==(const DeviceInfo& lhs, const DeviceInfo& rhs)
{
    return lhs.path == rhs.path && lhs.name == rhs.name;
}
