#include "Strategies/ReadDevicesStrategy/ReadLinuxDevices.h"

#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <iostream>
#include <map>

std::vector<DeviceInfo> ReadLinuxDevices::ReturnDevices()
{
    const std::string devicesDirectory {"/dev/input"};

    std::vector<DeviceInfo> devicesInfo;

    auto devicesFile {std::filesystem::directory_iterator(devicesDirectory)};

    std::map<DeviceId, DeviceInfo> devices;

    for (const auto& deviceFile : devicesFile)
    {
        const std::string path {deviceFile.path().string()};

        if (path.find("event") == std::string::npos)
        {
            continue;
        }

        int file {open(path.c_str(), O_RDONLY, O_NONBLOCK)};
        if (file < 0)
        {
            std::cerr << "Failed to open " << path.c_str() << std::endl;
            continue;
        }

        if (!IsAPeripheric(file))
        {
            close(file);
            continue;
        }

        char physicalLocation[256] = "";

        ioctl(file, EVIOCGPHYS(sizeof(physicalLocation)), physicalLocation);

        std::string physicalLocationString(physicalLocation);

        if (!physicalLocationString.empty() && physicalLocationString.back() != '0')
        {
            close(file);
            continue;
        }

        input_id id{};

        ioctl(file, EVIOCGID, &id);

        DeviceId deviceId{
            id.bustype,
            id.vendor,
            id.product,
            id.version
        };

        if (devices.contains(deviceId))
        {
            devices.at(deviceId).path.push_back(path);
        }
        else
        {
            char deviceName[256];
            ioctl(file, EVIOCGNAME(sizeof(deviceName)), deviceName);

            DeviceInfo deviceInfo;

            deviceInfo.path.push_back(path);
            deviceInfo.name = deviceName;

            devices.emplace(deviceId, deviceInfo);
        }

        close(file);
    }

    for (auto&& [deviceId, deviceInfo] : devices)
    {
        devicesInfo.push_back(deviceInfo);
    }

    return devicesInfo;
}

bool ReadLinuxDevices::TestBit(int bit, const uint8_t* array)
{
    return array[bit / 8] >> (bit % 8) & 1;
}

bool ReadLinuxDevices::IsAPeripheric(int file)
{
    uint8_t evBits [(EV_MAX  + 7) / 8] = {};
    uint8_t keyBits[(KEY_MAX + 7) / 8] = {};
    uint8_t relBits[(REL_MAX + 7) / 8] = {};
    uint8_t absBits[(ABS_MAX + 7) / 8] = {};

    ioctl(file, EVIOCGBIT(0, sizeof(evBits)), evBits);
    ioctl(file, EVIOCGBIT(EV_KEY, sizeof(keyBits)), keyBits);
    ioctl(file, EVIOCGBIT(EV_REL, sizeof(relBits)), relBits);
    ioctl(file, EVIOCGBIT(EV_ABS, sizeof(absBits)), absBits);

    bool hasKeys {TestBit(EV_KEY, evBits)};
    bool hasRel {TestBit(EV_REL, evBits)};
    bool hasAbs {TestBit(EV_ABS, evBits)};
    bool hasRelXY {TestBit(REL_X, relBits) && TestBit(REL_Y, relBits)};
    bool hasAbsXY {TestBit(ABS_X, absBits) && TestBit(ABS_Y, absBits)};

    bool isAMouse {hasRel && hasRelXY && TestBit(BTN_LEFT, keyBits)};
    bool isAKeyboard {hasKeys && TestBit(KEY_A, keyBits) && TestBit(KEY_SPACE, keyBits)};
    bool isAGamepad {hasAbs && TestBit(BTN_SOUTH, keyBits)};
    bool isAJoystick {hasAbs && hasAbsXY && TestBit(BTN_JOYSTICK, keyBits)};
    bool isATouchpad {hasAbs && hasAbsXY && TestBit(BTN_TOUCH, keyBits) && TestBit(BTN_TOOL_FINGER, keyBits)};

    return isAMouse || isAKeyboard || isAGamepad || isAJoystick || isATouchpad;
}