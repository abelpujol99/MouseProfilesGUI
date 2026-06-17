#pragma once

#include <wayland-client-protocol.h>
#include <xkbcommon/xkbcommon.h>

struct WaylandContext
{
    wl_display* display = nullptr;
    wl_registry* registry = nullptr;
    wl_seat* seat = nullptr;
    wl_keyboard* keyboard = nullptr;
    wl_pointer* pointer  = nullptr;
    xkb_context* xkbContext = nullptr;
    xkb_keymap* xkbKeymap = nullptr;
    xkb_state* xkbState = nullptr;
};
