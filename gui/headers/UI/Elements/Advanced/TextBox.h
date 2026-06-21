#pragma once
#include <map>

#include "UI/Helpers/ISelectable.h"

#include "UI/Elements/Intermediate/Rectangle.h"
#include "UI/Elements/Intermediate/Text/Text.h"
#include "Managers/Gestures/SelectableManager.h"
#include "Strategies/DrawStrategy/Rectangle/DrawEmptyRectangle.h"
#include "Strategies/DrawStrategy/Rectangle/DrawFilledRectangle.h"
#include "UI/Elements/Base/RectDrawable.h"

class TextBox : public DrawableComponent, public DrawableTransform, public ISelectable
{
public:

    TextBox(std::string placeHolder, bool isHidden = false);

    TextBox(const TextBox& other);

    ~TextBox() noexcept override;

    void SetRectangle(std::unique_ptr<Rectangle<DrawEmptyRectangle>>&& rectangle);

    void SetTextComponent(std::unique_ptr<Text>&& text);

    void SetIsHidden(bool isHidden) override;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    bool CanBeSelected() override;

    void OnSelect() override;

    void OnUnselect() override;

    void Subscribe() override;

    void Unsubscribe() override;

    void Enable() override;

    void Disable() override;

    [[nodiscard]] std::unique_ptr<TextBox> Clone() const;

    void Draw(ImDrawList* drawList) override;

private:

    void EraseSelection(size_t first, size_t last) const;

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    void MapSubscriptions();

    void CreateTextContainer();

    void UpdateTextContainerSize();

    __uint8_t _pointerPosition {0};

    int8_t _selectionCount {0};

    __uint16_t _textWidth;

    std::string _placeHolder;

    std::unique_ptr<Rectangle<DrawEmptyRectangle>> _rectangle;

    std::unique_ptr<Rectangle<DrawFilledRectangle>> _selectionRectangle;

    std::unique_ptr<RectDrawable> _textContainer;

    std::unique_ptr<Text> _text;

    std::map<std::string, std::function<void()>> _charPressedActions;

    std::weak_ptr<std::function<void(std::string)>> _onTypeCharAction;
};