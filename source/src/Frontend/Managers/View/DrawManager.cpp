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
    std::unique_ptr<Canvas> canvas = CanvasFactory::CreateDevicesCanvas(false);

    _currentCanvas = canvas.get();

    AddCanvas(std::move(canvas));
}

void DrawManager::AddCanvas(std::unique_ptr<Canvas> canvas)
{
    _canvas.push_back(std::move(canvas));
}

void DrawManager::DrawElements(ImDrawList* drawList)
{
    auto itEnd {_canvas.cend()};

    for (auto it {_canvas.begin()}; it != itEnd; ++it)
    {
        (*it)->Draw(drawList);
    }
}