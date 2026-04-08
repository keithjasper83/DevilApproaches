#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

struct Projectile
{
    int id;
    sf::Vector2f position;
    sf::Vector2f velocity;
    int damage;
    int targetFaction; // The faction this projectile intends to hit
    float lifetime;    // Max time the projectile lives

    Projectile(int id, sf::Vector2f startPos, sf::Vector2f dir, float speed, int damage, int targetFaction)
        : id(id), position(startPos), damage(damage), targetFaction(targetFaction), lifetime(5.0f)
    {
        // Normalize direction and apply speed
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length != 0) {
            velocity = sf::Vector2f((dir.x / length) * speed, (dir.y / length) * speed);
        } else {
            velocity = sf::Vector2f(0.f, 0.f);
        }
    }

    void update(float deltaTime)
    {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
        lifetime -= deltaTime;
    }

    bool isDead() const
    {
        return lifetime <= 0.0f;
    }
};
