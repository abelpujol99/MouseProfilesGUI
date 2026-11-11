#include "Command/Macro.h"

#include "Managers/DevicesManager.h"

Macro::Macro(std::vector<InputEvent>&& inputEvents) : _inputEvents(std::move(inputEvents))
{}

void Macro::Execute(DeviceId deviceId) const
{
    for (size_t i {0}; i < _inputEvents.size(); ++i)
    {
        DevicesManager::GetInstance().Emit(deviceId, {_inputEvents[i]});
    }
}