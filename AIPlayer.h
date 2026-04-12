#pragma once
#include "Level.h"
#include "Economy.h"

class AIPlayer
{
public:
    AIPlayer(Level& level, Faction faction);

    void update(float deltaTime);
    Economy& getEconomy();
    Faction getFaction() const;

private:
    Level& level;
    Economy economy;
    Faction faction;
    float actionTimer;

    // AI Behaviors
    void tryClaimTerritory();
    void tryBuildRoom();
};
