#pragma once
#include "BaseDisplay.h"

class DrawableTransform;
class ISubscriptionPosition;

class BaseDrawable : public BaseDisplay
{
public:

    ~BaseDrawable() override = default;

    virtual void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer,
        ImVec2* parentSizePointer, bool* isParentHiddenPointer);

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

protected:

    BaseDrawable(bool isHidden);

private:

    ImVec2* _parentPosition {nullptr};

    ImVec2* _parentBottomRightPosition {nullptr};
};