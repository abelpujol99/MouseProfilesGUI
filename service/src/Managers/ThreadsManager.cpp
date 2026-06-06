#include "Managers/ThreadsManager.h"

#include "Managers/MVPManager.h"
#include "TimeUsings.h"
#include "TimeDefines.h"

std::unique_ptr<ThreadsManager> ThreadsManager::_threadsManagerInstance = nullptr;

ThreadsManager& ThreadsManager::GetInstance()
{
    if (!_threadsManagerInstance)
    {
        _threadsManagerInstance.reset(new ThreadsManager());
    }

    return *_threadsManagerInstance;
}

void ThreadsManager::SetProfileAction(std::function<void()>&& profileAction)
{
    _mutex.lock();
    _profileAction = std::move(profileAction);
    _mutex.unlock();
}

void ThreadsManager::Start() {

    MVPManager::GetInstance().SubscribeToShouldRunObserver([&](bool value) {
        _shouldKeepRunning = value;
    });

    MVPManager::GetInstance().SubscribeToShouldGUIRunObserver([&](bool value) {
        _shouldGUIKeepRunning = value;
    });

    std::thread profileLoop {std::thread(&ThreadsManager::ProfileThreadLoop, this)};

    std::thread guiLoop {std::thread(&ThreadsManager::GUIThreadLoop, this)};

    for (auto& listenerThread : _listenersThreads)
    {
        listenerThread.join();
    }

    profileLoop.join();
    guiLoop.join();
}

void ThreadsManager::ProfileThreadLoop()
{
    while (_shouldKeepRunning)
    {
        if (_profileAction == nullptr)
        {
            std::this_thread::sleep_for(Duration(DEFAULT_THREAD_SLEEP_MILLIS));
            continue;
        }

        _mutex.lock();
        _profileAction();
        _profileAction = nullptr;
        _mutex.unlock();
    }
}

void ThreadsManager::GUIThreadLoop()
{
    while (_shouldKeepRunning)
    {
        if (!_shouldGUIKeepRunning)
        {
            std::this_thread::sleep_for(Duration(DEFAULT_THREAD_SLEEP_MILLIS));
            continue;
        }

        MVPManager::GetInstance().StartGUI();
    }
}
