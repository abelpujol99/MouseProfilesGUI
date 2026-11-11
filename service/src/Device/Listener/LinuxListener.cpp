#include "Device/Listener/LinuxListener.h"

#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <linux/uinput.h>

#include "Input/InputEvent.h"
#include "Managers/DevicesManager.h"

#define TIMEOUT_MILLIS 100

LinuxListener::LinuxListener(DeviceId deviceId, std::string&& filePath) :
    _listenerThread(std::thread(&LinuxListener::ListenerUpdate, this, deviceId, std::move(filePath)))
{}

void LinuxListener::ListenerUpdate(DeviceId deviceId, std::string&& filePath) const
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

    while (_keepLooping.load())
    {
        if (ReadWithTimeout(readFile, &event, sizeof(event)) <= 0)
        {
            continue;
        }

        if (event.type == EV_SYN && event.code == SYN_REPORT)
        {
            DevicesManager::GetInstance().RegisterInputEvents(deviceId, std::move(inputEvents));
            inputEvents.clear();
            continue;
        }

        inputEvents.emplace_back(event.type, event.code, event.value);
    }

    ioctl(readFile, EVIOCGRAB, 0);
    close(readFile);
}

void LinuxListener::StopListener()
{
    _keepLooping.store(false);

    if (!_listenerThread.joinable())
    {
        return;
    }

    _listenerThread.join();
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
