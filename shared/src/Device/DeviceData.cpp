#include "Device/DeviceData.h"

DeviceData::DeviceData(uint16_t busType, uint16_t vendor, uint16_t product, uint16_t version) : _busType(busType),
    _vendor(vendor), _product(product), _version(version)
{}

uint16_t DeviceData::GetBusType() const
{
    return _busType;
}

uint16_t DeviceData::GetVendor() const
{
    return _vendor;
}

uint16_t DeviceData::GetProduct() const
{
    return _product;
}

uint16_t DeviceData::GetVersion() const
{
    return _version;
}
