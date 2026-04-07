#pragma once
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

namespace sf {
    class VideoMode {
    public:
        unsigned int width;
        unsigned int height;
        unsigned int bitsPerPixel;
        VideoMode() : width(0), height(0), bitsPerPixel(0) {}
        VideoMode(unsigned int w, unsigned int h, unsigned int b = 32) : width(w), height(h), bitsPerPixel(b) {}
        static VideoMode getDesktopMode() { return VideoMode(1920, 1080); }
    };

    namespace Style {
        enum { None = 0, Titlebar = 1, Resize = 2, Close = 4, Fullscreen = 8, Default = Titlebar | Resize | Close };
    }

    class Window {
    public:
        void create(VideoMode mode, const std::string& title, unsigned int style = Style::Default) {}
        void close() {}
        bool isOpen() const { return true; }
        void setTitle(const std::string& title) {}
        bool pollEvent(Event& event) { return false; }
        Vector2u getSize() const { return Vector2u(800, 600); }
        void display() {}
    };

    class View {
    public:
        View() {}
        View(const FloatRect& rectangle) {}
    };

    class RenderWindow : public Window {
    public:
        void draw(const class Drawable&) {}
        void clear() {}
        void setView(const View& view) {}
        View getDefaultView() const { return View(); }
    };
}
