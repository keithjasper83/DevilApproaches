#include "Level.h"

Level::Level(float width, float height) : size(width, height)
{
    background.setSize(size);
    background.setFillColor(sf::Color::Black);
}

void Level::draw(sf::RenderWindow &window)
{
    window.draw(background);
}

sf::Vector2f Level::getSize() const
{
    return size;
}
