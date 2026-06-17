#pragma once
#include "BaseProcessDataStrategy.h"

#include <functional>
#include <memory>

class DisplayKey : public BaseProcessDataStrategy
{
public:

    ~DisplayKey() override = default;

    void StartProcessData() override;

    void StopProcessData() override;

private:

    std::weak_ptr<std::function<void(const char*)>> _onKeyPressedAction;

};