#pragma once
#include "BaseDisplay.h"

class BaseDrawable : public BaseDisplay
{
public:

    ~BaseDrawable() override = default;

    virtual void SetParentTransform(ImVec2* parentPosition, ImVec2* parentBottomRightPosition, ImVec2* parentSize);

protected:

    BaseDrawable(bool isHidden);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] ImVec2 GetParentSize() const override;

private:

    ImVec2* _parentPosition {nullptr};

    ImVec2* _parentBottomRightPosition {nullptr};

    ImVec2* _parentSize {nullptr};
};