#pragma once

#include <string>

#include <ICommand.h>

class StringCommand : public ICommand
{
private:
    std::string _commandLine;

public:

    StringCommand(std::string&& commandLine);

    std::string GetCommandLine() const;

    void Execute() override;
};