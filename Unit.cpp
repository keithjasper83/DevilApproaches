#include "Unit.h"
#include <algorithm>

Unit::Unit(int id, UnitType type, float x, float y, int faction)
    : id(id), type(type), position(x, y), faction(faction), currentJob(JobType::Idle), morale(100), currentCooldown(0.0f)
{
    if (type == UnitType::Fighter) {
        maxHp = 100;
        attackDamage = 20;
        attackRange = 30.0f; // Melee
        attackCooldown = 1.0f;
    } else if (type == UnitType::Ranger) {
        maxHp = 60;
        attackDamage = 15;
        attackRange = 150.0f; // Ranged
        attackCooldown = 2.0f;
    } else {
        maxHp = 50;
        attackDamage = 5;
        attackRange = 20.0f;
        attackCooldown = 1.5f;
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

float Unit::getAttackRange() const
{
    return attackRange;
}

float Unit::getAttackCooldown() const
{
    return attackCooldown;
}

float Unit::getCurrentCooldown() const
{
    return currentCooldown;
}

void Unit::resetCooldown()
{
    currentCooldown = attackCooldown;
}

bool Unit::canAttack() const
{
    return currentCooldown <= 0.0f;
}

void Unit::update(float deltaTime)
{
    if (currentCooldown > 0.0f) {
        currentCooldown -= deltaTime;
    }

    // Basic simulation hook for future AI state machines
    if (currentJob == JobType::Idle)
    {
        // Minimal morale decay when idle
        // modifyMorale(-1);
    }
}
