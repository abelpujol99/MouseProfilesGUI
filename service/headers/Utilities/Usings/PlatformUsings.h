#pragma once

#ifdef __linux__
#include "Device/VirtualDevice/LinuxVirtualDevice.h"
#include "Device/Listener/LinuxListener.h"
#include "Device/Emitter/LinuxEmitter.h"

    using PlatformVirtualDevice = LinuxVirtualDevice;
    using PlatformListener = LinuxListener;
    using PlatformEmitter = LinuxEmitter;
    using PlatformListenerData = std::string;
#elif defined(__WIN32)
#include "Device/VirtualDevice/WindowsVirtualDevice.h"
#include "Device/Listener/WindowsListener.h"
#include "Device/Emitter/WindowsEmitter.h"

    using PlatformVirtualDevice = WindowsVirtualDevice;
    using PlatformListener = WindowsListener;
    using PlatformEmitter = WindowsEmitter;
    using PlatformListenerData;
#endif