#pragma once
#include <SFML/System.hpp>
#include <string>

namespace sf {
    class Window {
    public:
        void close() {}
    };

    struct Event {
        enum { Closed } type;
    };

    class RenderWindow : public Window {
    public:
        void draw(const class Drawable&) {}
    };
}
