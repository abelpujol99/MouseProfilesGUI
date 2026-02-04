#pragma once

#include <string>

#include <ICommand.h>

class SwitchScrollModeCommand : public ICommand
{
private:

    std::string _filePath;

    bool _isInFreeMode;

    bool IsInFreeMode();

public:

    SwitchScrollModeCommand();

    ~SwitchScrollModeCommand() override = default;

    void Execute() override;
};
