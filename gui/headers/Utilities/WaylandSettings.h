#pragma once

#include <wayland-client-protocol.h>

struct WaylandSettings
{
    wl_display*  display  = nullptr;
    wl_registry* registry = nullptr;
    wl_seat*     seat     = nullptr;
    wl_keyboard* keyboard = nullptr;
    wl_pointer*  pointer  = nullptr;
};