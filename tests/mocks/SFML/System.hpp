#pragma once

namespace sf {
    template <typename T>
    struct Vector2 {
        T x, y;
        Vector2() : x(0), y(0) {}
        Vector2(T x, T y) : x(x), y(y) {}
    };
    typedef Vector2<float> Vector2f;
}
