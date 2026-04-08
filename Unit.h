#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Requires forward declaration or inclusion of Faction from Level.h
enum class Faction;

enum class UnitType
{
    Worker,
    Fighter,
    Ranger
};

enum class JobType
{
    Idle,
    Digging,
    Training,
    Fighting
};

class Unit
{
public:
    Unit(int id, UnitType type, float x, float y, int faction);

    int getId() const;
    UnitType getType() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

    int getFaction() const;

    JobType getCurrentJob() const;
    void setJob(JobType job);

    int getMorale() const;
    void modifyMorale(int amount);

    int getHp() const;
    int getMaxHp() const;
    void takeDamage(int amount);
    bool isDead() const;
    int getAttackDamage() const;

    float getAttackRange() const;
    float getAttackCooldown() const;
    float getCurrentCooldown() const;
    void resetCooldown();
    bool canAttack() const;

    void update(float deltaTime);

private:
    int id;
    UnitType type;
    sf::Vector2f position;
    int faction; // Stored as int to break cyclic dependency with Level.h's Faction, handled via cast in manager
    JobType currentJob;
    int morale;

    int hp;
    int maxHp;
    int attackDamage;
    float attackRange;
    float attackCooldown;
    float currentCooldown;
};
