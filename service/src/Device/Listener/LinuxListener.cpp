#include "Device/Listener/LinuxListener.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <linux/uinput.h>

#include "Input/InputEvent.h"
#include "Managers/DevicesManager.h"

#define TIMEOUT_MILLIS 100

void LinuxListener::ListenerUpdate(DeviceId deviceId, std::string&& filePath)
{
    int readFile {open(filePath.c_str(), O_RDONLY | O_NONBLOCK)};

    if (readFile < 0)
    {
        std::cerr << "Failed to open " << filePath << std::endl;
        return;
    }

    ioctl(readFile, EVIOCGRAB, 1);

    input_event event{};

    std::vector<InputEvent> inputEvents;

    while (_keepLooping)
    {
        _mutex.unlock();

        if (ReadWithTimeout(readFile, &event, sizeof(event)) <= 0)
        {
            continue;
        }

        if (event.type == EV_SYN && event.code == SYN_REPORT)
        {
            DevicesManager::GetInstance().RegisterInputEvents(deviceId, std::move(inputEvents));
            continue;
        }

        inputEvents.emplace_back(event.type, event.code, event.value);

        _mutex.lock();
    }

    ioctl(readFile, EVIOCGRAB, 0);
    close(readFile);
}

void LinuxListener::StopListener()
{
    _mutex.lock();
    _keepLooping = false;
    _mutex.unlock();
}

ssize_t LinuxListener::ReadWithTimeout(int readFile, void* buffer, size_t size)
{
    pollfd pollFile {};
    pollFile.fd = readFile;
    pollFile.events = POLLIN;

    if (poll(&pollFile, 1, TIMEOUT_MILLIS) <= 0)
    {
        return 0;
    }

    return read(readFile, buffer, size);
}
