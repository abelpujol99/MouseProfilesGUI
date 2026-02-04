#include <CommandDecorator.h>

CommandDecorator::CommandDecorator(std::unique_ptr<ICommand>&& command) : _command(std::move(command))
{}