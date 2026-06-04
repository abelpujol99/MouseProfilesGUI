#include "Managers/View/WindowManager.h"

#define WIDTH 1500
#define HEIGHT 700

int main()
{
    WindowManager& windowManager {WindowManager::GetInstance()};

    windowManager.SetInitialSize(WIDTH, HEIGHT);
    windowManager.Start();
    windowManager.Update();

    return 0;
}