#include "Backend/Listener/HidrawListener.h"

#include <fcntl.h>

#include "Backend/Managers/VirtualDeviceManager.h"

HidrawListener::HidrawListener(FileCodes&& fileCodes)
    : BaseListener(std::move(fileCodes)), _numberOfInputs(_codes.size())
{}

void HidrawListener::ListenerUpdate()
{
    int file = open(_filePath.c_str(), O_RDONLY, O_NONBLOCK);

    if (file < 0)
    {
        throw std::runtime_error("Failed to open " + _filePath);
    }

    const size_t bytesCount {_numberOfInputs};

    unsigned char fileData[bytesCount];

    std::unordered_set<unsigned char> lastButtonsPressed;
    std::unordered_set<unsigned char> currentButtonsPressed;

    lastButtonsPressed.reserve(_numberOfInputs);
    currentButtonsPressed.reserve(_numberOfInputs);

    while (_keepLooping)
    {
        if (ReadWithTimeout(file, &fileData, sizeof(fileData), TIMEOUT_MILLIS) <= 0)
        {
            continue;
        }

        currentButtonsPressed.clear();
        currentButtonsPressed.reserve(_numberOfInputs);

        for (size_t i {0}; i < bytesCount; ++i)
        {
            if (!_codes.contains(fileData[i]))
            {
                continue;
            }
            currentButtonsPressed.emplace(fileData[i]);
        }

        for (const auto& code : _codes)
        {
            if (currentButtonsPressed.contains(code) && !lastButtonsPressed.contains(code))
            {
                VirtualDeviceManager::RegisterHidrawInputEvent(code, 1);
            }
            else if (lastButtonsPressed.contains(code) && !currentButtonsPressed.contains(code))
            {
                VirtualDeviceManager::RegisterHidrawInputEvent(code, 0);
            }
        }

        lastButtonsPressed = currentButtonsPressed;
    }

    close(file);
}