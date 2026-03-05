#pragma once
namespace sf {
    class Time {
    public:
        Time() {}
        float asSeconds() const { return 0.f; }
    };
    inline Time seconds(float amount) { return Time(); }
}
