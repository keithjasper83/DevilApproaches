#include "Unit.h"
#include <algorithm>

Unit::Unit(int id, UnitType type, float x, float y, int faction)
    : id(id), type(type), position(x, y), faction(faction), currentJob(JobType::Idle), morale(100)
{
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

void Unit::update(float deltaTime)
{
    // Basic simulation hook for future AI state machines
    if (currentJob == JobType::Idle)
    {
        // Minimal morale decay when idle
        // modifyMorale(-1);
    }
}
