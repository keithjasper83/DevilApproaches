#include "AIPlayer.h"
#include "Level.h"
#include <iostream>

int main() {
    Level level(400.0f, 400.0f);
    AIPlayer ai(level, Faction::Enemy1);

    // Verify initial state
    if (ai.getFaction() != Faction::Enemy1) {
        std::cerr << "Test Failed: AI Faction is incorrect." << std::endl;
        return 1;
    }

    if (ai.getEconomy().getResource(ResourceType::Ore) != 0) {
        std::cerr << "Test Failed: Initial Ore balance should be 0." << std::endl;
        return 1;
    }

    // Run AI update for 2+ seconds to trigger an action (TryClaimTerritory)
    // Initially, AI has 0 Ore, so it should claim territory and gain 10 Ore
    ai.update(2.1f);

    if (ai.getEconomy().getResource(ResourceType::Ore) != 10) {
        std::cerr << "Test Failed: AI did not gain Ore after claiming territory." << std::endl;
        return 1;
    }

    // Force Ore to trigger a room build
    ai.getEconomy().addResource(ResourceType::Ore, 100);

    // Run AI update for another 2+ seconds
    // AI has >50 Ore, so it should spend 50 Ore to build a room
    ai.update(2.1f);

    if (ai.getEconomy().getResource(ResourceType::Ore) != 60) { // 10 + 100 - 50 = 60
        std::cerr << "Test Failed: AI did not spend Ore to build a room, or math is wrong." << std::endl;
        return 1;
    }

    std::cout << "Test Passed: AI Player mechanics are correct." << std::endl;
    return 0;
}
