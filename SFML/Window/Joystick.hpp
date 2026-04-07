#pragma once
#include <string>
namespace sf {
    class String {
    public:
        std::string toAnsiString() const { return ""; }
    };
    class Joystick {
    public:
        enum { Count = 8, ButtonCount = 32 };
        enum Axis { X, Y, Z, R, U, V, PovX, PovY };
        struct Identification {
            String name;
            unsigned int vendorId;
            unsigned int productId;
        };
        static bool isConnected(unsigned int joystick) { return false; }
        static bool isButtonPressed(unsigned int joystick, unsigned int button) { return false; }
        static float getAxisPosition(unsigned int joystick, Axis axis) { return 0.0f; }
        static Identification getIdentification(unsigned int joystick) { return Identification(); }
    };
}
