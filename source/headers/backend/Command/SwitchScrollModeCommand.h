#pragma once

#include <string>

#include "backend/Command/ICommand.h"

class SwitchScrollModeCommand : public ICommand
{
public:

    SwitchScrollModeCommand();

    ~SwitchScrollModeCommand() override = default;

    void Execute() override;

private:

    std::string _filePath;

    bool _isInFreeMode;

    bool IsInFreeMode();
};