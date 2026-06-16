#pragma once
#include <cstdint>
#include <asm-generic/int-ll64.h>

#include "IReadDevicesStrategy.h"

class ReadLinuxDevices : public IReadDevicesStrategy
{
public:

    ~ReadLinuxDevices() override = default;

    [[nodiscard]] std::vector<DeviceInfo> ReturnDevices() override;

private:

    struct DeviceId
    {
        __u16 bustype;
        __u16 vendor;
        __u16 product;
        __u16 version;

        auto operator<=>(const DeviceId& other) const = default;
    };

    bool TestBit(int bit, const uint8_t* array);

    bool IsAPeripheric(int file);

};