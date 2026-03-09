#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream> // Include the necessary header for std::stringstream

class WindowManager
{
  public:
    sf::Font font;
    sf::Text text;
    sf::RenderWindow window;
    sf::Event event;
    WindowManager();
    ~WindowManager();
    void createWindow();
    bool isActive();
    void updateWindowTitle(float fps, sf::Vector2f playerPosition);
    void closeWindow();
    void drawText(const std::string &content, float x, float y);

  private:
    sf::Clock titleUpdateClock;
    const sf::Time titleUpdateInterval = sf::seconds(0.2f);
};
