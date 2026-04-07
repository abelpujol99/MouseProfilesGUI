#pragma once
#include "UI/RectDrawable.h"
#include "UI/Structs/RectangleData.h"
#include "UI/Structs/TextData.h"

enum class TextVerticalAlignments;
enum class TextHorizontalAlignments;
enum class FontFamilyTypes;

class Button : public RectDrawable
{

public:

    Button(DrawablePosition&& drawablePosition, RectangleData&& rectangleData, TextData&& textData, bool isHidden);

    ~Button() override = default;

    void Draw(ImDrawList *drawList) override;




};
