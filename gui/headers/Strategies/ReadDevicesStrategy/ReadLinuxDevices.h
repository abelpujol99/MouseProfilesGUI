#pragma once
#include <cstdint>

#include "IReadDevicesStrategy.h"

class ReadLinuxDevices : public IReadDevicesStrategy
{
public:

    ~ReadLinuxDevices() override = default;

    [[nodiscard]] std::vector<DeviceInfo> ReturnDevices() override;

private:

    bool TestBit(int bit, const uint8_t* array);

    bool IsAPeripheric(int file);

};