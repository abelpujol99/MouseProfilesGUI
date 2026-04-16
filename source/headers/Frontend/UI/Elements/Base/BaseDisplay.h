#pragma once

#include <memory>

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

    void SetParentIsHidden(bool* isParentHidden);

    [[nodiscard]] bool IsParentHidden() const;

    virtual void UpdateVisibility();

    [[nodiscard]] bool MustBeHidden() const;

    bool _isHidden;

    std::unique_ptr<bool> _mustBeHidden {std::make_unique<bool>()};

private:

    ImVec2* _parentSize {nullptr};

    bool* _isParentHidden;
};