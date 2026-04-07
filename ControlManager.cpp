#include "ControlManager.h"

void ControlManager::isJoystickConnected()
{
    // Get the number of connected joysticks
    unsigned int joystickCount = sf::Joystick::Count;
    std::cout << "Number of connected joysticks: " << joystickCount << std::endl;

    // Iterate over each connected joystick
    for (unsigned int i = 0; i < joystickCount; ++i)
    {
        // Get the identification information for the current joystick
        sf::Joystick::Identification identification = sf::Joystick::getIdentification(i);

        // Output the identification information
        std::cout << "Joystick ID: " << i << std::endl;
        std::cout << "  Name: " << identification.name.toAnsiString() << std::endl;
        std::cout << "  Vendor ID: " << identification.vendorId << std::endl;
        std::cout << "  Product ID: " << identification.productId << std::endl;
    }
}

sf::Vector2f ControlManager::getPlayerMovement()
{
    // todo: CLEAN CODE
    sf::Vector2f movement(0.f, 0.f);
    float speed = 1.f;
    if (shifting())
    {
        speed = 0.5f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed;
    return movement;
}

bool ControlManager::shifting()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}
bool ControlManager::shouldExitGame()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}
bool ControlManager::shouldResetGame()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
}

sf::Vector2f ControlManager::getControllerMovement(unsigned int joystickId)
{
    // TODO: IMPLEMENT SLOW MOVEMENT
    //  Check if the joystick is connected
    if (sf::Joystick::isConnected(joystickId))
    {
        // Get the position of the left joystick

        // TODO: implement custom definitions for the buttons FOR BETTER MAPPING
        float x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
        float y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);
        // Apply deadzone to avoid slight drift
        const float deadzone = 5.f;
        if (std::abs(x) < deadzone)
            x = 0.f;
        if (std::abs(y) < deadzone)
            y = 0.f;

        //  Normalize the values to get movement direction
        return sf::Vector2f(x / 100.f, y / 100.f);
    }
    // Return zero movement if the joystick is not connected
    return sf::Vector2f(0.f, 0.f);
}

bool ControlManager::shouldExitGame(unsigned int joystickId)
{
    // Check if the joystick is connected
    if (sf::Joystick::isConnected(joystickId))
    {
        // Check if the button 8 is pressed (Start Key on xbox controller)
        return sf::Joystick::isButtonPressed(joystickId, 7);
    }
    // Return false if the joystick is not connected
    return false;
}


bool ControlManager::shouldResetGame(unsigned int joystickId)
{
    // Check if the joystick is connected
    if (sf::Joystick::isConnected(joystickId))
    {
        // Check if the button 7 is pressed (Select Key on xbox controller)
        return sf::Joystick::isButtonPressed(joystickId, 6);
    }
    // Return false if the joystick is not connected
    return false;
}

void ControlManager::pollEvents(sf::RenderWindow &window) // Pass reference to sf::RenderWindow
{
    sf::Event event;
    while (window.pollEvent(event)) // Call pollEvent on sf::RenderWindow object
    {
        if (event.type == sf::Event::Closed)
        {
            // Handle window close event
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // Handle key press event
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            // Handle key release event
        }
        else if (event.type == sf::Event::JoystickMoved)
        {
            // Handle joystick movement event
        }
        else if (event.type == sf::Event::JoystickButtonPressed)
        {
            // Output button ID if pressed
            for (int button = 0; button < sf::Joystick::ButtonCount; ++button)
            {
                if (sf::Joystick::isButtonPressed(0, button))
                {
                    std::cout << "Button pressed: " << button << std::endl;
                }
            }
            // Handle joystick button press event
        }
        // Add more event types as needed
    }
}
