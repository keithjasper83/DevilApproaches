#include "Level.h"
#include <cmath>

Level::Level(float width, float height) : size(width, height)
{
    background.setSize(size);
    background.setFillColor(sf::Color::Black);

    gridWidth = static_cast<int>(std::ceil(size.x / tileSize));
    gridHeight = static_cast<int>(std::ceil(size.y / tileSize));

    grid.resize(gridWidth * gridHeight, TileType::Dirt);
    ownershipGrid.resize(gridWidth * gridHeight, Faction::Neutral);
    roomGrid.resize(gridWidth * gridHeight, RoomType::None);
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

void Level::dig(float worldX, float worldY)
{
    int gridX = static_cast<int>(worldX / tileSize);
    int gridY = static_cast<int>(worldY / tileSize);

    if (getTile(gridX, gridY) == TileType::Dirt)
    {
        setTile(gridX, gridY, TileType::Empty);
    }
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
}

sf::Vector2f Level::getSize() const
{
    return size;
}
