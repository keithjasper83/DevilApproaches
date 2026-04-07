#pragma once
#include "Level.h"
#include "Economy.h"
#include <SFML/Graphics.hpp>

class Player
{
  public:
    Player(const Level &level);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    void move(float x, float y);
    void setStartPosition();

    Economy& getEconomy(); // Accessor for player economy

  private:
    sf::CircleShape shape;
    sf::Vector2f position;
    const Level &level;
    Economy economy;
};
