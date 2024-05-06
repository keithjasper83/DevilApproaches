#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

class ControlManager
{
  public:
    static void isJoystickConnected();
    static sf::Vector2f getPlayerMovement();
    static bool shifting();
    static bool shouldExitGame();
    static bool shouldResetGame();
    static sf::Vector2f getControllerMovement(unsigned int joystickId); // New function for controller input
    static bool shouldExitGame(unsigned int joystickId);                // New function for controller input
    static bool shouldResetGame(unsigned int joystickId);               // New function for controller input
    static void pollEvents(sf::RenderWindow &window);
};
