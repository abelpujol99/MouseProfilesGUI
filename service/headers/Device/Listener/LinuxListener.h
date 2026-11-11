#pragma once

#include <mutex>
#include <string>

#include "DeviceUsings.h"

class LinuxListener
{
public:

    LinuxListener() = default;

    LinuxListener(const LinuxListener& other) = delete;
    LinuxListener& operator=(const LinuxListener& other) = delete;
    LinuxListener(LinuxListener&& other) = delete;
    LinuxListener& operator=(LinuxListener&& other) = delete;

    ~LinuxListener() = default;

    void ListenerUpdate(DeviceId deviceId, std::string&& filePath);

    void StopListener();

private:

    static ssize_t ReadWithTimeout(int readFile, void* buffer, size_t size);

    bool _keepLooping {true};

    std::mutex _mutex;
};
