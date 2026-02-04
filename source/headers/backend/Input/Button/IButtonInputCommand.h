#pragma once
#include <IInputCommand.h>

class IButtonInputCommand : public IInputCommand
{
public:

    virtual ~IButtonInputCommand() = default;

    virtual void ExecuteCommand() = 0;

    virtual void Stop() = 0;

    virtual int GetState() const = 0;
};
