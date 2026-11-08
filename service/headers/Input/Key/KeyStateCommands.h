#pragma once
#include <memory>

class ICommand;

struct KeyStateCommands
{
    std::unique_ptr<ICommand const> onPress;

    std::unique_ptr<ICommand const> onHold;

    std::unique_ptr<ICommand const> onRelease;
};
