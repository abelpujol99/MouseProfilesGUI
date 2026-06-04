#pragma once
#include <memory>

#include "UI/Helpers/IDrawable.h"

class BaseDisplay : public IDrawable
{
public:

    ~BaseDisplay() override = default;

    void SetIsHidden(bool isHidden);

    [[nodiscard]] bool IsHidden() const;

    [[nodiscard]] ImVec2 GetParentSize() const override;

protected:

    BaseDisplay(bool isHidden);

    virtual void SetParentSizePointer(ImVec2* parentSizePointer);

    virtual void SetIsParentHiddenPointer(bool* isParentHiddenPointer);

    std::unique_ptr<bool> _mustBeHidden;

private:

    bool _isHidden;

    bool* _isParentHidden {nullptr};

    ImVec2* _parentSize {nullptr};
};