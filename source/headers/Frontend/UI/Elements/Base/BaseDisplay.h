#pragma once
#include "Frontend/UI/Helpers/IDrawable.h"

class BaseDisplay : public IDrawable
{
public:

    ~BaseDisplay() override = default;

    void SetIsHidden(bool isHidden);

    [[nodiscard]] bool IsHidden() const;

protected:

    BaseDisplay(bool isHidden);

    virtual void SetParentSizePointer(ImVec2* parentSizePointer);

    [[nodiscard]] ImVec2 GetParentSize() const override;

    bool _isHidden;

private:

    ImVec2* _parentSize {nullptr};
};
