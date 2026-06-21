#pragma once
#include "Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"
#include "UI/Helpers/IClickable.h"

#include "UI/Elements/Intermediate/Rectangle.h"
#include "UI/Elements/Intermediate/Text/Text.h"

class Button : public DrawableComponent, public IClickable
{

public:

    Button(std::function<void()>&& action, bool isHidden);

    Button(const Button& other);

    ~Button() noexcept override;

    void SetIsHidden(bool isHidden) override;

    void SetRectangle(std::unique_ptr<Rectangle<DrawFilledRectangle>>&& foregroundRectangle);

    void SetTextComponent(std::unique_ptr<Text>&& text);

    void SetText(std::string&& text) const;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    void OnParentSizeUpdated() override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    [[nodiscard]] bool CanBeClicked() const override;

    void SetAction(std::function<void()>&& action);

    void Click() override;

    void Subscribe() override;

    void Unsubscribe() override;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<Button> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<Rectangle<DrawFilledRectangle>> _rectangle;

    std::unique_ptr<Text> _text;

    std::function<void()> _action;
};