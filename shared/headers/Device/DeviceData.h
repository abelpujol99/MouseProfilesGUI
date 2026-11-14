#pragma once
#include <compare>
#include <cstdint>
#include <array>

class DeviceData
{
public:

    DeviceData(std::array<char, 80> name, uint16_t busType, uint16_t vendor, uint16_t product, uint16_t version);

    [[nodiscard]] std::array<char, 80> GetName() const;
    [[nodiscard]] uint16_t GetBusType() const;
    [[nodiscard]] uint16_t GetVendor() const;
    [[nodiscard]] uint16_t GetProduct() const;
    [[nodiscard]] uint16_t GetVersion() const;

private:

    std::array<char, 80> _name {};
    uint16_t _busType;
    uint16_t _vendor;
    uint16_t _product;
    uint16_t _version;

    auto operator<=>(const DeviceData& other) const = default;
};