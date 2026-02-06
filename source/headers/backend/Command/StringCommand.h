#pragma once

#include <string>

#include "backend/Command/ICommand.h"

class StringCommand : public ICommand
{
public:

    StringCommand(std::string&& commandLine);

    std::string GetCommandLine() const;

    void Execute() override;

private:
    std::string _commandLine;
};