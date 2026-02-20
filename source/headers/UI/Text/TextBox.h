#pragma once
#include "UI/RectDrawable.h"

#include <memory>
#include <functional>

class Text;
enum class TextHorizontalAlignments;
enum class TextVerticalAlignments;
enum class FontFamilyTypes;

class TextBox : public RectDrawable
{
public:

    TextBox(const ImVec2& parentPosition, float positionX, float positionY, int width, int height,
        float verticalPadding, float horizontalPadding, ImColor color, float rounding, float thickness,
        TextHorizontalAlignments textHorizontalAlignment, TextVerticalAlignments textVerticalAlignment, FontFamilyTypes textFont,
        float fontSize, ImColor textColor, bool isHidden = false);

    ~TextBox() override = default;

    void UpdatePosition() override;

    void Draw(ImDrawList* drawList) override;

private:

    std::unique_ptr<Text> _text;

    ImColor _color;

    float _verticalPadding;

    float _horizontalPadding;

    float _rounding;

    float _thickness;

    std::weak_ptr<std::function<void(bool)>> _onLeftMouseButtonReleasedWeakAction;

    bool _hasLeftMouseButtonReleased{false};

    bool _isSelected{false};
};
