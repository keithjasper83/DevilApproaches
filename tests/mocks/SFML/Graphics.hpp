#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

namespace sf {
    class Drawable {};

    class Color {
    public:
        Color(int r, int g, int b, int a = 255) {}
        static const Color Red;
        static const Color Black;
    };

    inline const Color Color::Red = Color(255, 0, 0);
    inline const Color Color::Black = Color(0, 0, 0);

    class Shape : public Drawable {
    public:
        virtual ~Shape() {}
        void setFillColor(const Color& color) {}
        void setOutlineColor(const Color& color) {}
        void setOutlineThickness(float thickness) {}
        void setPosition(float x, float y) {}
        void setPosition(const Vector2f& pos) {}
        void setOrigin(float x, float y) {}
    };

    class CircleShape : public Shape {
    public:
        void setRadius(float radius) {}
    };

    class RectangleShape : public Shape {
    public:
        void setSize(const Vector2f& size) {}
    };

    class Font {
    public:
        bool loadFromFile(const std::string& filename) { return true; }
    };

    class Text : public Drawable {
    public:
        void setFont(const Font& font) {}
        void setString(const std::string& str) {}
        void setCharacterSize(unsigned int size) {}
        void setFillColor(const Color& color) {}
        void setPosition(float x, float y) {}
    };
}
