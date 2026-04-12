#pragma once
#include "Backend/Input/Strategy/IHoldState.h"
#include "Backend/Input/Strategy/IReleaseState.h"

#include "TimeUsings.h"

class IMouseInputState : public IHoldState, public IReleaseState
{

public:

    ~IMouseInputState() override = default;

    [[nodiscard]] virtual const Duration& GetFirstTimeDelay() const = 0;

    [[nodiscard]] virtual const Duration& GetMillisToRepeatInput() const = 0;
};