#pragma once

#include "Frontend/UI/IDrawable.h"

class BaseDisplay : public IDrawable
{
public:

    BaseDisplay(bool isHidden);

    ~BaseDisplay() override = default;

    void SetIsHidden(bool isHidden);

    [[nodiscard]] bool IsHidden() const;

protected:

    bool _isHidden;
};