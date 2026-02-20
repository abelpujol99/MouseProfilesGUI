#include <csignal>
#include "backend/Listener/EvdevListener.h"

#include <fcntl.h>
#include <iostream>
#include <linux/input.h>

#include "backend/Managers/ProfileManager.h"
#include "backend/Managers/VirtualDeviceManager.h"
#include "backend/Input/InputEvent.h"

EvdevListener::EvdevListener(FileCodes&& fileCodes) : BaseListener(std::move(fileCodes))
{}

void EvdevListener::ListenerUpdate()
{
    int file {open(_filePath.c_str(), O_RDONLY, O_NONBLOCK)};

    if (file < 0)
    {
        std::cerr << "Failed to open " << _filePath << std::endl;
        return;
    }

    ioctl(file, EVIOCGRAB, 1);

    input_event event{};

    while (_keepLooping)
    {
        if (ReadWithTimeout(file, &event, sizeof(event), TIMEOUT_MILLIS) <= 0)
        {
            continue;
        }

        VirtualDeviceManager::GetInstance().RegisterEvdevInputEvent(InputEvent(event.type, event.code, event.value));
    }

    ioctl(file, EVIOCGRAB, 0);
    close(file);
}