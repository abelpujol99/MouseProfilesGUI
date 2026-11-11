#pragma once
#include <compare>
#include <cstdint>

class DeviceData
{
public:

    DeviceData(uint16_t busType, uint16_t vendor, uint16_t product, uint16_t version);

    [[nodiscard]] uint16_t GetBusType() const;
    [[nodiscard]] uint16_t GetVendor() const;
    [[nodiscard]] uint16_t GetProduct() const;
    [[nodiscard]] uint16_t GetVersion() const;

private:

    //TODO DEVICE NAME
    uint16_t _busType;
    uint16_t _vendor;
    uint16_t _product;
    uint16_t _version;

    auto operator<=>(const DeviceData& other) const = default;
};