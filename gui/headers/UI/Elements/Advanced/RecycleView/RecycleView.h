#pragma once
#include "Utilities/Concepts/DerivedFromBaseDrawable.h"

#include <vector>
#include <memory>
#include <map>
#include <cmath>

#include "Managers/Gestures/ScrollableManager.h"
#include "UI/Helpers/IScrollable.h"
#include "Utilities/Math.h"
#include "ColorDefines.h"
#include "RecycleViewActions.h"
#include "UI/Elements/Base/DrawableComponent.h"
#include "UI/Elements/Base/DrawableTransform.h"
#include "UI/Elements/Base/RectDrawable.h"

#define SCROLL_MULTIPLIER 10

class RecycleView : public DrawableComponent, public DrawableTransform, public IScrollable
{
public:

    RecycleView(uint8_t viewsPerRow, ImVec2&& marginBetweenViews, ImVec2&& rowsSize, uint8_t bufferRows,
        std::function<void(RectDrawable*)>&& addDefault, std::function<void()> removeLastView,
        RecycleViewActions&& devicesPresenterActions, bool isHidden = false);

    ~RecycleView() noexcept override;

    void SetIsHidden(bool isHidden) override;

    void SetParentState(ImVec2* parentPositionPointer, ImVec2* parentBottomRightPositionPointer, ImVec2* parentSizePointer,
        bool* isParentHiddenPointer) override;

    [[nodiscard]] ImVec2 GetParentPosition() const override;

    [[nodiscard]] ImVec2 GetParentBottomRightPosition() const override;

    bool CanBeScrolled() override;

    void Scroll(float scrollValue) override;

    void SetCurrentScroll(float currentScroll);

    void SetIsFirstItemPresent(bool isFirstItemPresent);

    void SetIsLastItemPresent(bool isLastItemPresent);

    void Enable() override;

    void Disable() override;

    void Draw(ImDrawList* drawList) override;

private:

    void OnParentPositionUpdated() override;

    void OnParentBottomRightPositionUpdated() override;

    void OnParentSizeUpdated() override;

    void UpdateResizableDrawablesCount();

    void CreateRow(ImVec2&& lastRowPosition);

    void DeleteLastRow();

    void HandleMove();

    uint8_t _viewsPerRow;

    ImVec2 _marginBetweenViews;

    ImVec2 _rowsSize;

    uint8_t _bufferRows;

    float _widthPerView;

    std::vector<std::unique_ptr<RectDrawable>> _rows;

    std::map<RectDrawable*, std::vector<RectDrawable*>> _views;

    float _currentScroll {0};

    bool _isFirstItemPresent;

    bool _isLastItemPresent;

    std::function<void(RectDrawable*)> _addDefault;

    std::function<void()> _removeLastViewComponents;

    RecycleViewActions _devicesPresenterActions;
};