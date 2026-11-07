#include "Command/Macro.h"

#include "Managers/VirtualDeviceManager.h"

Macro::Macro(std::vector<EmitData>&& emitsData) : _emitsData(std::move(emitsData))
{}

void Macro::Execute() const
{
    for (size_t i {0}; i < _emitsData.size(); ++i)
    {
        VirtualDeviceManager::GetInstance().Emit(_emitsData[i].GetInputDevice(), _emitsData[i].GetInputEvent());
        VirtualDeviceManager::GetInstance().Emit(_emitsData[i].GetInputDevice(), InputEvent(EV_SYN, SYN_REPORT, 0));
    }
}
