#include "Level.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>

Level::Level(float width, float height) : size(width, height)
{
    background.setSize(size);
    background.setFillColor(sf::Color::Black);

    gridWidth = static_cast<int>(std::ceil(size.x / tileSize));
    gridHeight = static_cast<int>(std::ceil(size.y / tileSize));

    grid.resize(gridWidth * gridHeight, TileType::Dirt);
    ownershipGrid.resize(gridWidth * gridHeight, Faction::Neutral);
    roomGrid.resize(gridWidth * gridHeight, RoomType::None);
    spatialGrid.resize(gridWidth * gridHeight);
}

void Level::setTile(int x, int y, TileType type)
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        grid[y * gridWidth + x] = type;
    }
}

TileType Level::getTile(int x, int y) const
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        return grid[y * gridWidth + x];
    }
    return TileType::SolidRock; // Out of bounds is solid rock
}

bool Level::dig(float worldX, float worldY)
{
    int gridX = static_cast<int>(std::floor(worldX / tileSize));
    int gridY = static_cast<int>(std::floor(worldY / tileSize));

    if (getTile(gridX, gridY) == TileType::Dirt)
    {
        setTile(gridX, gridY, TileType::Empty);
        return true;
    }
    return false;
}

void Level::claimTile(int x, int y, Faction faction)
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        // Only allow claiming of non-solid tiles
        if (getTile(x, y) != TileType::SolidRock)
        {
            ownershipGrid[y * gridWidth + x] = faction;
        }
    }
}

Faction Level::getTileFaction(int x, int y) const
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        return ownershipGrid[y * gridWidth + x];
    }
    return Faction::Neutral; // Out of bounds is neutral
}

void Level::buildRoom(int x, int y, RoomType type)
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        // Enforce rule: Room can only be built on Empty tiles claimed by the Player
        if (getTile(x, y) == TileType::Empty && getTileFaction(x, y) == Faction::Player)
        {
            roomGrid[y * gridWidth + x] = type;
        }
    }
}

RoomType Level::getRoom(int x, int y) const
{
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight)
    {
        return roomGrid[y * gridWidth + x];
    }
    return RoomType::None; // Out of bounds is None
}

void Level::addUnit(Unit unit)
{
    units.push_back(unit);
}

int Level::getGridIndex(float x, float y) const
{
    int gridX = static_cast<int>(std::floor(x / tileSize));
    int gridY = static_cast<int>(std::floor(y / tileSize));
    if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
        return gridY * gridWidth + gridX;
    }
    return -1; // Out of bounds
}

void Level::updateUnits(float deltaTime)
{
    // Update individual unit state and movement
    for (auto& unit : units)
    {
        unit.update(deltaTime);

        // Extremely basic placeholder logic: if idle, assign random movement
        if (unit.getCurrentJob() == JobType::Idle)
        {
            sf::Vector2f pos = unit.getPosition();

            // Random walk (very naive placeholder)
            float moveX = ((rand() % 3) - 1) * 10.0f * deltaTime;
            float moveY = ((rand() % 3) - 1) * 10.0f * deltaTime;

            float newX = std::max(0.0f, std::min(pos.x + moveX, size.x));
            float newY = std::max(0.0f, std::min(pos.y + moveY, size.y));

            unit.setPosition(newX, newY);
        }
    }

    // Spatial Partitioning for combat
    // Clear the reused spatial grid
    for (auto& cell : spatialGrid) {
        cell.clear();
    }

    // Populate spatial grid
    for (size_t i = 0; i < units.size(); ++i)
    {
        if (units[i].isDead()) continue;

        sf::Vector2f pos = units[i].getPosition();
        int index = getGridIndex(pos.x, pos.y);
        if (index != -1) {
            spatialGrid[index].push_back(i);
        }
    }

    // Check for collisions using the spatial grid
    for (size_t i = 0; i < units.size(); ++i)
    {
        if (units[i].isDead()) continue;

        sf::Vector2f pos = units[i].getPosition();
        int gridX = static_cast<int>(std::floor(pos.x / tileSize));
        int gridY = static_cast<int>(std::floor(pos.y / tileSize));

        float attackRange = units[i].getAttackRange();
        int searchRadius = static_cast<int>(std::ceil(attackRange / tileSize));

        // Check the unit's cell and surrounding cells within attackRange
        for (int dy = -searchRadius; dy <= searchRadius; ++dy)
        {
            for (int dx = -searchRadius; dx <= searchRadius; ++dx)
            {
                int checkX = gridX + dx;
                int checkY = gridY + dy;

                if (checkX >= 0 && checkX < gridWidth && checkY >= 0 && checkY < gridHeight)
                {
                    int cellIndex = checkY * gridWidth + checkX;
                    for (size_t j : spatialGrid[cellIndex])
                    {
                        if (i == j) continue; // Don't check against self
                        if (units[j].isDead()) continue;

                        // Check if they are from different factions
                        if (units[i].getFaction() != units[j].getFaction())
                        {
                            sf::Vector2f pos1 = units[i].getPosition();
                            sf::Vector2f pos2 = units[j].getPosition();
                            float distSq = (pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y);

                            if (distSq <= attackRange * attackRange)
                            {
                                if (units[i].canAttack())
                                {
                                    if (units[i].getType() == UnitType::Ranger)
                                    {
                                        // Spawn projectile
                                        sf::Vector2f dir(pos2.x - pos1.x, pos2.y - pos1.y);
                                        projectiles.emplace_back(projectileIdCounter++, pos1, dir, 200.0f, units[i].getAttackDamage(), units[j].getFaction());
                                    }
                                    else
                                    {
                                        // Melee attack
                                        units[j].takeDamage(units[i].getAttackDamage());
                                    }
                                    units[i].resetCooldown();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    updateProjectiles(deltaTime, spatialGrid);

    // Clean up dead units
    units.erase(
        std::remove_if(units.begin(), units.end(), [](const Unit& u) { return u.isDead(); }),
        units.end()
    );
}

void Level::updateProjectiles(float deltaTime, const std::vector<std::vector<size_t>>& spatialGrid)
{
    for (auto& proj : projectiles)
    {
        proj.update(deltaTime);

        // Simple collision check against the spatial grid
        sf::Vector2f projPos = proj.position;
        int gridX = static_cast<int>(std::floor(projPos.x / tileSize));
        int gridY = static_cast<int>(std::floor(projPos.y / tileSize));

        float hitRadiusSq = 15.0f * 15.0f; // Roughly the size of a unit + projectile
        bool hit = false;

        // Check 3x3 area
        for (int dy = -1; dy <= 1 && !hit; ++dy)
        {
            for (int dx = -1; dx <= 1 && !hit; ++dx)
            {
                int checkX = gridX + dx;
                int checkY = gridY + dy;

                if (checkX >= 0 && checkX < gridWidth && checkY >= 0 && checkY < gridHeight)
                {
                    int cellIndex = checkY * gridWidth + checkX;
                    for (size_t uIdx : spatialGrid[cellIndex])
                    {
                        Unit& target = units[uIdx];
                        if (target.isDead() || target.getFaction() != proj.targetFaction) continue;

                        sf::Vector2f uPos = target.getPosition();
                        float distSq = (projPos.x - uPos.x) * (projPos.x - uPos.x) + (projPos.y - uPos.y) * (projPos.y - uPos.y);

                        if (distSq <= hitRadiusSq)
                        {
                            target.takeDamage(proj.damage);
                            proj.lifetime = 0.0f; // Destroy projectile
                            hit = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Clean up dead projectiles
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) { return p.isDead(); }),
        projectiles.end()
    );
}

void Level::draw(sf::RenderWindow &window)
{
    window.draw(background);

    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));

    // Create an inner shape to represent ownership/faction claiming
    const float claimMargin = 4.0f;
    sf::RectangleShape claimShape(sf::Vector2f(tileSize - 2 * claimMargin, tileSize - 2 * claimMargin));

    // Create an inner shape to represent rooms
    const float roomMargin = 8.0f;
    sf::RectangleShape roomShape(sf::Vector2f(tileSize - 2 * roomMargin, tileSize - 2 * roomMargin));

    // Drawing all tiles for now, as mock headers lack view getter methods
    int startX = 0;
    int startY = 0;
    int endX = gridWidth;
    int endY = gridHeight;

    for (int y = startY; y < endY; ++y)
    {
        for (int x = startX; x < endX; ++x)
        {
            TileType type = grid[y * gridWidth + x];
            if (type == TileType::SolidRock)
            {
                tileShape.setFillColor(sf::Color(100, 100, 100)); // Dark Grey
            }
            else if (type == TileType::Dirt)
            {
                tileShape.setFillColor(sf::Color(139, 69, 19)); // SaddleBrown
            }
            else if (type == TileType::Empty)
            {
                // Empty tiles don't get the base dirt/rock drawing, but can still show ownership
                tileShape.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent representation
            }

            if (type != TileType::Empty) {
                tileShape.setPosition(x * tileSize, y * tileSize);
                window.draw(tileShape);
            }

            // Draw ownership overlay if not neutral
            Faction faction = ownershipGrid[y * gridWidth + x];
            if (faction != Faction::Neutral)
            {
                if (faction == Faction::Player)
                {
                    claimShape.setFillColor(sf::Color(0, 0, 255, 128)); // Semi-transparent Blue
                }
                else if (faction == Faction::Enemy1)
                {
                    claimShape.setFillColor(sf::Color(255, 0, 0, 128)); // Semi-transparent Red
                }

                claimShape.setPosition(x * tileSize + claimMargin, y * tileSize + claimMargin);
                window.draw(claimShape);
            }

            // Draw room overlay
            RoomType roomType = roomGrid[y * gridWidth + x];
            if (roomType != RoomType::None)
            {
                if (roomType == RoomType::Production)
                {
                    roomShape.setFillColor(sf::Color(255, 215, 0)); // Gold/Yellow
                }
                else if (roomType == RoomType::Training)
                {
                    roomShape.setFillColor(sf::Color(178, 34, 34)); // Firebrick Red
                }
                else if (roomType == RoomType::Research)
                {
                    roomShape.setFillColor(sf::Color(75, 0, 130)); // Indigo/Purple
                }

                roomShape.setPosition(x * tileSize + roomMargin, y * tileSize + roomMargin);
                window.draw(roomShape);
            }
        }
    }

    // Draw Units
    sf::CircleShape unitShape(10.0f);
    unitShape.setOrigin(10.0f, 10.0f); // Center origin for easy positioning
    for (const auto& unit : units)
    {
        unitShape.setPosition(unit.getPosition());

        if (unit.getType() == UnitType::Worker)
        {
            unitShape.setFillColor(sf::Color(139, 69, 19)); // Brown
        }
        else if (unit.getType() == UnitType::Fighter)
        {
            unitShape.setFillColor(sf::Color(178, 34, 34)); // Dark Red
        }

        // Faction indicator could be a border color, keeping it simple for now
        if (unit.getFaction() == static_cast<int>(Faction::Player))
        {
            unitShape.setOutlineColor(sf::Color(0, 0, 255)); // Blue
            unitShape.setOutlineThickness(2.0f);
        }
        else
        {
            unitShape.setOutlineColor(sf::Color(255, 0, 0)); // Red
            unitShape.setOutlineThickness(2.0f);
        }

        window.draw(unitShape);
    }

    // Draw Projectiles
    sf::CircleShape projShape(4.0f);
    projShape.setFillColor(sf::Color(255, 255, 0)); // Yellow
    projShape.setOrigin(4.0f, 4.0f);
    for (const auto& proj : projectiles)
    {
        projShape.setPosition(proj.position);
        window.draw(projShape);
    }
}

sf::Vector2f Level::getSize() const
{
    return size;
}
