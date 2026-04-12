#pragma once
#include "BaseDrawable.h"

class DrawableComponent : public BaseDrawable
{
public:

    DrawableComponent(bool isHidden);

    ~DrawableComponent() override = default;

    virtual void SetBottomRightPositionPointer(ImVec2* bottomRightPositionPointer);

protected:

    [[nodiscard]] ImVec2 GetBottomRightPosition() const override;

private:

    ImVec2* _bottomRightPosition {nullptr};
};