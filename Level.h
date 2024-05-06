#pragma once
#include <SFML/Graphics.hpp>

class Level
{
  public:
    Level(float width, float height);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getSize() const;

  private:
    sf::RectangleShape background;
    sf::Vector2f size = sf::Vector2f(4000, 4000);
};
