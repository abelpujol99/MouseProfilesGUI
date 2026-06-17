#pragma once
#include "BaseProcessDataStrategy.h"

#include <functional>
#include <map>
#include <memory>

class ApplyKey : public BaseProcessDataStrategy
{
public:

    ApplyKey();

    ~ApplyKey() override = default;

    void StartProcessData() override;

    void StopProcessData() override;

private:

    std::map<std::string, std::function<void()>> _charPressedActions;

    std::weak_ptr<std::function<void(std::string)>> _onCharPressedAction;
};