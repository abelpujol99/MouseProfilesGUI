#pragma once

#include <forward_list>
#include <functional>
#include <mutex>
#include <thread>
#include "Utilities/Usings/PlatformUsings.h"

class ThreadsManager
{
public:

    ~ThreadsManager() = default;

    ThreadsManager(const ThreadsManager& other) = delete;
    ThreadsManager& operator=(const ThreadsManager& other) = delete;

    static ThreadsManager& GetInstance();

    void CreateListenerThread(PlatformListener& platformListener, DeviceId deviceId, PlatformListenerData&& platformListenerData);

    void SetDevicesHoldAction(std::function<void()>&& profileAction);

    void Start();

private:

    ThreadsManager() = default;

    void ProfileThreadLoop();

    void GUIThreadLoop();

    static std::unique_ptr<ThreadsManager> _threadsManagerInstance;

    std::forward_list<PlatformListener> _listeners;

    std::forward_list<std::thread> _listenersThreads;

    bool _shouldKeepRunning {true};

    bool _shouldGUIKeepRunning {true};

    std::function<void()> _profileAction = nullptr;

    std::mutex _mutex;
};