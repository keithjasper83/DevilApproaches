#pragma once
#include <SFML/System/Time.hpp>
namespace sf {
    class Clock {
    public:
        Time getElapsedTime() const { return Time(); }
        Time restart() { return Time(); }
    };
}
