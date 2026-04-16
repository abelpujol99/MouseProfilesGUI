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

    virtual void SetParentSize(ImVec2* parentSize);

    [[nodiscard]] ImVec2 GetParentSize() const override;

    bool _isHidden;

private:

    ImVec2* _parentSize {nullptr};
};