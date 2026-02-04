#pragma once

class IInputCommand
{
public:

    virtual ~IInputCommand() = default;

    virtual void ExecuteCommand() const = 0;

    //TODO VISITOR
};