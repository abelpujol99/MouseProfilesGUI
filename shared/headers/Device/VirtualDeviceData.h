#pragma once
#include <unordered_map>
#include <unordered_set>

#include "Utilities/Usings/PlatformUsings.h"

class VirtualDeviceData
{
public:
    VirtualDeviceData(std::unordered_map<unsigned long, std::unordered_set<int>>&& capableInputs,
        const PlatformDeviceData& platformDeviceData);

    [[nodiscard]] std::unordered_map<unsigned long, std::unordered_set<int>> GetCapableInputs() const;
    [[nodiscard]] PlatformDeviceData GetDeviceData() const;

private:

    std::unordered_map<unsigned long, std::unordered_set<int>> _capableInputs;

    PlatformDeviceData _platformDeviceData;

};
