#pragma once
#include "BaseProcessDataStrategy.h"

#include <functional>
#include <memory>

class ApplyKey : public BaseProcessDataStrategy
{
public:

    ~ApplyKey() override = default;

    void StartProcessData() override;

    void StopProcessData() override;

private:

    std::weak_ptr<std::function<void(std::string)>> _onCharPressedAction;

};