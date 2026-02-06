#pragma once
#include "backend/State/IHoldState.h"
#include "backend/State/IReleaseState.h"

#include <TimeUsings.h>

class IMouseInputState : public IHoldState, public IReleaseState
{

public:

    virtual ~IMouseInputState() = default;

    virtual const Duration& GetFirstTimeDelay() const = 0;

    virtual const Duration& GetMillisToRepeatInput() const = 0;
};