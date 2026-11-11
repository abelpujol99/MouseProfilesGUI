#pragma once

#include <thread>
#include <string>

#include "DeviceUsings.h"

class LinuxListener
{
public:

    LinuxListener(DeviceId deviceId, std::string&& filePath);

    LinuxListener(const LinuxListener& other) = delete;
    LinuxListener& operator=(const LinuxListener& other) = delete;
    LinuxListener(LinuxListener&& other) = delete;
    LinuxListener& operator=(LinuxListener&& other) = delete;

    ~LinuxListener() = default;

    void StopListener();

private:

    void ListenerUpdate(DeviceId deviceId, std::string&& filePath) const;

    static ssize_t ReadWithTimeout(int readFile, void* buffer, size_t size);

    std::atomic<bool> _keepLooping {true};

    std::thread _listenerThread;
};
