#include "Backend/Command/Decorator/BaseCommandDecorator.h"

BaseCommandDecorator::BaseCommandDecorator(std::unique_ptr<ICommand>&& command) : _command(std::move(command))
{}