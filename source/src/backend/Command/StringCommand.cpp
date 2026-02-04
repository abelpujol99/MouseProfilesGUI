#include <StringCommand.h>

StringCommand::StringCommand(std::string&& commandLine) :_commandLine(std::move(commandLine))
{}

std::string StringCommand::GetCommandLine() const
{
    return _commandLine;
}

void StringCommand::Execute()
{
    system(_commandLine.c_str());
}