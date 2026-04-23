#include "Frontend/Managers/View/DrawManager.h"

#include "Frontend/Factory/CanvasFactory.h"

DrawManager* DrawManager::_drawManagerInstance {nullptr};

DrawManager::~DrawManager() noexcept
{
    delete _drawManagerInstance;
}

DrawManager& DrawManager::GetInstance()
{
    if (_drawManagerInstance == nullptr)
    {
        _drawManagerInstance = new DrawManager();
    }

    return *_drawManagerInstance;
}

void DrawManager::Start()
{
    _currentCanvas = CanvasFactory::CreateProfileCanvas(false);

    AdsCanvas(_currentCanvas.get());
}

void DrawManager::AdsCanvas(Canvas* canvas)
{
    _canvas.push_back(canvas);
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    auto itEnd {_canvas.cend()};

    for (auto it {_canvas.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}