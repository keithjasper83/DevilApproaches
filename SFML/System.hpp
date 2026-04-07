#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

namespace sf {
    template <typename T>
    struct Vector2 {
        T x, y;
        Vector2() : x(0), y(0) {}
        Vector2(T x, T y) : x(x), y(y) {}
    };
    typedef Vector2<float> Vector2f;
    typedef Vector2<unsigned int> Vector2u;

    template <typename T>
    struct Rect {
        T left, top, width, height;
        Rect() : left(0), top(0), width(0), height(0) {}
        Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) : left(rectLeft), top(rectTop), width(rectWidth), height(rectHeight) {}
    };
    typedef Rect<float> FloatRect;
}
