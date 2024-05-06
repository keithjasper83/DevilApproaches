#include "WindowManager.h"

WindowManager::WindowManager()
{
    // configure the window defaults
}

WindowManager::~WindowManager()
{
    // clean up the window
    std::cout << "Window destroyed" << std::endl;
}

void WindowManager::createWindow()
{
    // Adjust video mode and style to support full screen
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    window.create(desktopMode, "Your Game Title", sf::Style::Fullscreen);

    // Load font
    font.loadFromFile("OpenSans-Regular.ttf");

    // Set up text properties
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

bool WindowManager::isActive()
{
    return window.isOpen();
}
void WindowManager::updateWindowTitle(float fps, sf::Vector2f playerPosition)
{
    std::stringstream ss;
    ss << "My window - FPS: " << fps << " - Player Position: (" << playerPosition.x << ", " << playerPosition.y << ")";
    window.setTitle(ss.str());
}

void WindowManager::closeWindow()
{
    window.close();
}

void WindowManager::drawText(const std::string &content, float x, float y)
{
    text.setString(content);
    text.setPosition(x, y);
    window.draw(text);
}
