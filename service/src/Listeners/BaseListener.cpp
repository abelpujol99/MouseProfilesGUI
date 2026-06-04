#include "Listener/BaseListener.h"

#include <iostream>
#include <poll.h>
#include <unistd.h>

#include "Managers/ApplicationManager.h"
#include "Profile/FileCodes.h"

BaseListener::BaseListener(FileCodes&& fileCodes) : _filePath(std::move(fileCodes.GetFilePath())), _codes(std::move(fileCodes.GetCodes()))
{
    _shouldRunListenerAction =
        ApplicationManager::GetInstance().SubscribeToShouldRunObserver([&](bool value) {
            std::cout << "Stop Listeners" << std::endl;
            _keepLooping = value;
        });
}

ssize_t BaseListener::ReadWithTimeout(int file, void* buffer, size_t size, int timeoutMillis)
{
    pollfd pollFile;
    pollFile.fd = file;
    pollFile.events = POLLIN;

    int ret {poll(&pollFile, 1, timeoutMillis)};

    if (ret <= 0)
    {
        return 0;
    }

    return read(file, buffer, size);
}