#include "Player.h"

Player::Player(const Level &level) : level(level)
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20, 20); // Center the origin
}
void Player::setPosition(float x, float y)
{
    position.x = std::max(0.f, std::min(x, level.getSize().x));
    position.y = std::max(0.f, std::min(y, level.getSize().y));
    shape.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return position;
}
void Player::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
void Player::move(float offsetX, float offsetY)
{
    setPosition(position.x + offsetX, position.y + offsetY);
}

void Player::setStartPosition()
{
    setPosition(level.getSize().x / 2, level.getSize().y / 2);
}

Economy& Player::getEconomy()
{
    return economy;
}
