#pragma once

#include <functional>
#include <memory>
#include <unordered_set>

#include "../../../shared/usings/CodeUsings.h"

class FileCodes;

#define TIMEOUT_MILLIS 20

class BaseListener
{
public:

    virtual ~BaseListener() = default;

    virtual void ListenerUpdate() = 0;

protected:

    BaseListener(FileCodes&& fileCodes);

    ssize_t ReadWithTimeout(int file, void* buffer, size_t size, int timeoutMillis);

    bool _keepLooping {true};

    std::weak_ptr<std::function<void(bool)>> _shouldRunListenerAction;

    std::string _filePath;

    std::unordered_set<Code> _codes;

};