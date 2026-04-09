#pragma once

#include <memory>

#include "IPosition.h"

struct DrawablePosition;

class Drawable : public IPosition
{
public:

    virtual ~Drawable() = default;

    void SetIsHidden(bool isHidden);

    void SetParentPosition(const ImVec2& parentPosition) const;

    [[nodiscard]] const ImVec2& GetParentPosition() const;

    [[nodiscard]] virtual const ImVec2& GetRelativePosition() const;

    [[nodiscard]] ImVec2* GetPosition() const override;

    virtual void UpdatePosition();

    virtual void Draw(ImDrawList* drawList) = 0;

protected:

    Drawable(DrawablePosition&& drawablePosition, bool isHidden);

    ImVec2& _parentPosition;
    ImVec2 _relativePosition;
    std::unique_ptr<ImVec2> _position;

    bool _isHidden;
};
