#include "Unit.h"
#include <algorithm>

Unit::Unit(int id, UnitType type, float x, float y, int faction)
    : id(id), type(type), position(x, y), faction(faction), currentJob(JobType::Idle), morale(100)
{
    if (type == UnitType::Fighter) {
        maxHp = 100;
        attackDamage = 20;
    } else {
        maxHp = 50;
        attackDamage = 5;
    }
    hp = maxHp;
}

int Unit::getId() const
{
    return id;
}

UnitType Unit::getType() const
{
    return type;
}

sf::Vector2f Unit::getPosition() const
{
    return position;
}

void Unit::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

int Unit::getFaction() const
{
    return faction;
}

JobType Unit::getCurrentJob() const
{
    return currentJob;
}

void Unit::setJob(JobType job)
{
    currentJob = job;
}

int Unit::getMorale() const
{
    return morale;
}

void Unit::modifyMorale(int amount)
{
    morale += amount;
    // Clamp morale between 0 and 100
    morale = std::max(0, std::min(100, morale));
}

int Unit::getHp() const
{
    return hp;
}

int Unit::getMaxHp() const
{
    return maxHp;
}

void Unit::takeDamage(int amount)
{
    if (amount > 0) {
        hp -= amount;
        hp = std::max(0, hp);
    }
}

bool Unit::isDead() const
{
    return hp <= 0;
}

int Unit::getAttackDamage() const
{
    return attackDamage;
}

void Unit::update(float deltaTime)
{
    // Basic simulation hook for future AI state machines
    if (currentJob == JobType::Idle)
    {
        // Minimal morale decay when idle
        // modifyMorale(-1);
    }
}
