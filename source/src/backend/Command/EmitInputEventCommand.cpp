#include <EmitInputEventCommand.h>
#include <iostream>

#include "VirtualDeviceManager.h"

EmitInputEventCommand::EmitInputEventCommand(std::vector<EmitData>&& emitsData) : _emitsData(std::move(emitsData))
{}

void EmitInputEventCommand::Execute()
{
    for (size_t i {0}; i < _emitsData.size(); ++i)
    {
        VirtualDeviceManager::GetInstance().Emit(_emitsData[i].GetInputDevice(), _emitsData[i].GetInputEvent());
        VirtualDeviceManager::GetInstance().Emit(_emitsData[i].GetInputDevice(), InputEvent(EV_SYN, SYN_REPORT, 0));
    }
}
