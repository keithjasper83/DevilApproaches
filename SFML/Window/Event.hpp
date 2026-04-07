#pragma once

namespace sf {
    struct Event {
        enum EventType {
            Closed,
            KeyPressed,
            KeyReleased,
            JoystickMoved,
            JoystickButtonPressed
        };
        EventType type;
        struct KeyEvent {
            int code;
            bool alt;
            bool control;
            bool shift;
            bool system;
        };
        union {
            KeyEvent key;
        };
    };
}
