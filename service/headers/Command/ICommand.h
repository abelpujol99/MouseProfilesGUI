#pragma once

class ICommand
{

public:

    virtual ~ICommand() = default;

    virtual void Execute() const = 0;
};