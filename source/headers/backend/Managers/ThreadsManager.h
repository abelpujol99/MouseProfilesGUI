#pragma once

#include <forward_list>
#include <thread>

#include <FileCodes.h>
#include <BaseListener.h>

#include "TimeUsings.h"

template <class TBaseListener>
concept DerivedFromBaseListener = std::is_base_of_v<BaseListener, TBaseListener>;

class ThreadsManager
{
private:

    static std::unique_ptr<ThreadsManager> _threadsManagerInstance;

    std::forward_list<std::unique_ptr<BaseListener>> _listeners;

    std::forward_list<std::thread> _listenersThreads;

    bool _shouldKeepRunning {true};

    std::function<void()> _profileAction = nullptr;

    std::mutex _mutex;

    ThreadsManager() = default;

    void ProfileThreadLoop();

public:

    ~ThreadsManager() = default;

    ThreadsManager(const ThreadsManager& other) = delete;
    ThreadsManager& operator=(const ThreadsManager& other) = delete;

    static ThreadsManager& GetInstance();

    template <DerivedFromBaseListener TBaseListener>
    void CreateListenersThreads(std::forward_list<FileCodes>&& fileCodes);

    void SetProfileAction(std::function<void()>&& profileAction);

    void Start();
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