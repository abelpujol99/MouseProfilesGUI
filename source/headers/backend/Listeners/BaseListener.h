#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include "backend/CodeUsing.h"

class FileCodes;

#define TIMEOUT_MILLIS 20

class BaseListener
{
public:

    virtual ~BaseListener() = default;

    virtual void ListenerUpdate() = 0;

protected:

    bool _keepLooping {true};

    std::weak_ptr<std::function<void(bool)>> _shouldRunListenerAction;

    std::string _filePath;

    std::unordered_set<Code> _codes;

    BaseListener(FileCodes&& fileCodes);

    ssize_t ReadWithTimeout(int file, void* buffer, size_t size, int timeoutMillis);

};