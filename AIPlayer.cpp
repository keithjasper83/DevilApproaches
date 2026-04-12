#include "AIPlayer.h"
#include <cstdlib>

AIPlayer::AIPlayer(Level& level, Faction faction)
    : level(level), faction(faction), actionTimer(0.0f)
{
}

Economy& AIPlayer::getEconomy()
{
    return economy;
}

Faction AIPlayer::getFaction() const
{
    return faction;
}

void AIPlayer::update(float deltaTime)
{
    actionTimer -= deltaTime;

    // AI takes an action every 2 seconds
    if (actionTimer <= 0.0f)
    {
        actionTimer = 2.0f;

        // Simple Decision Tree
        // If we have enough Ore (e.g., 50), try to build a room
        if (economy.getResource(ResourceType::Ore) >= 50)
        {
            tryBuildRoom();
        }
        else
        {
            // Otherwise, claim territory and passively gain Ore
            tryClaimTerritory();
            economy.addResource(ResourceType::Ore, 10);
        }
    }
}

void AIPlayer::tryClaimTerritory()
{
    sf::Vector2f levelSize = level.getSize();
    int gridWidth = static_cast<int>(levelSize.x / level.tileSize);
    int gridHeight = static_cast<int>(levelSize.y / level.tileSize);

    // Naive AI: Scan grid for an unclaimed tile next to a claimed one, or just claim a random tile if starting
    bool hasTerritory = false;
    for (int y = 0; y < gridHeight; ++y)
    {
        for (int x = 0; x < gridWidth; ++x)
        {
            if (level.getTileFaction(x, y) == faction)
            {
                hasTerritory = true;
                break;
            }
        }
        if (hasTerritory) break;
    }

    // Initial claim
    if (!hasTerritory)
    {
        int startX = rand() % gridWidth;
        int startY = rand() % gridHeight;

        // Dig and claim
        level.dig(startX * level.tileSize, startY * level.tileSize);
        level.claimTile(startX, startY, faction);
        return;
    }

    // Expand territory
    for (int y = 0; y < gridHeight; ++y)
    {
        for (int x = 0; x < gridWidth; ++x)
        {
            if (level.getTileFaction(x, y) == Faction::Neutral)
            {
                // Check if adjacent to owned territory
                bool adjacent = false;
                if (x > 0 && level.getTileFaction(x - 1, y) == faction) adjacent = true;
                if (x < gridWidth - 1 && level.getTileFaction(x + 1, y) == faction) adjacent = true;
                if (y > 0 && level.getTileFaction(x, y - 1) == faction) adjacent = true;
                if (y < gridHeight - 1 && level.getTileFaction(x, y + 1) == faction) adjacent = true;

                if (adjacent)
                {
                    level.dig(x * level.tileSize, y * level.tileSize);
                    level.claimTile(x, y, faction);
                    return; // One claim per action
                }
            }
        }
    }
}

void AIPlayer::tryBuildRoom()
{
    sf::Vector2f levelSize = level.getSize();
    int gridWidth = static_cast<int>(levelSize.x / level.tileSize);
    int gridHeight = static_cast<int>(levelSize.y / level.tileSize);

    // Find a claimed empty tile without a room
    for (int y = 0; y < gridHeight; ++y)
    {
        for (int x = 0; x < gridWidth; ++x)
        {
            if (level.getTileFaction(x, y) == faction &&
                level.getTile(x, y) == TileType::Empty &&
                level.getRoom(x, y) == RoomType::None)
            {
                // To build, actually deduct the cost
                if (economy.spendResource(ResourceType::Ore, 50))
                {
                    level.buildRoom(x, y, RoomType::Production);
                    return; // Build one room per action
                }
            }
        }
    }
}
