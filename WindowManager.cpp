#include "WindowManager.h"

WindowManager::WindowManager()
{
    // configure the window defaults
    titleUpdateInterval = sf::seconds(0.2f);
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
    if (titleUpdateClock.getElapsedTime().asSeconds() >= titleUpdateInterval.asSeconds())
    {
        std::stringstream ss;
        ss << "My window - FPS: " << static_cast<int>(fps) << " - Player Position: (" << static_cast<int>(playerPosition.x) << ", " << static_cast<int>(playerPosition.y) << ")";
        window.setTitle(ss.str());
        titleUpdateClock.restart();
    }
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
