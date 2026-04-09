#pragma once

#include <forward_list>
#include <thread>

#include "Backend/Listener/BaseListener.h"

template <class TBaseListener>
concept DerivedFromBaseListener = std::is_base_of_v<BaseListener, TBaseListener>;

class ThreadsManager
{
public:

    ~ThreadsManager() = default;

    ThreadsManager(const ThreadsManager& other) = delete;
    ThreadsManager& operator=(const ThreadsManager& other) = delete;

    static ThreadsManager& GetInstance();

    template <DerivedFromBaseListener TBaseListener>
    void CreateListenersThreads(std::forward_list<FileCodes>&& fileCodes);

    void SetProfileAction(std::function<void()>&& profileAction);

    void Start();

private:

    ThreadsManager() = default;

    void ProfileThreadLoop();

    void GUIThreadLoop();

    static std::unique_ptr<ThreadsManager> _threadsManagerInstance;

    std::forward_list<std::unique_ptr<BaseListener>> _listeners;

    std::forward_list<std::thread> _listenersThreads;

    bool _shouldKeepRunning {true};

    bool _shouldGUIKeepRunning {true};

    std::function<void()> _profileAction = nullptr;

    std::mutex _mutex;
};

template<DerivedFromBaseListener TBaseListener>
void ThreadsManager::CreateListenersThreads(std::forward_list<FileCodes>&& fileCodes)
{
    for (auto& fileCode : fileCodes)
    {
        _listeners.emplace_front(std::make_unique<TBaseListener>(std::move(fileCode)));
        _listenersThreads.emplace_front(&BaseListener::ListenerUpdate, _listeners.front().get());
    }
}