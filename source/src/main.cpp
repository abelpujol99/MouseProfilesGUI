#include "imgui.h"
#include "Managers/ApplicationManager.h"

int main()
{
    ApplicationManager::GetInstance().Start();

    return 0;
}