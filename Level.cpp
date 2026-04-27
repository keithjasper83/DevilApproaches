#include "Level.h"
#include <cmath>
#include <algorithm>

Level::Level(float width, float height) : size(width, height)
{
    background.setSize(size);
    background.setFillColor(sf::Color::Black);

    gridWidth = static_cast<int>(std::ceil(size.x / tileSize));
    gridHeight = static_cast<int>(std::ceil(size.y / tileSize));

    grid.resize(gridWidth * gridHeight, TileType::Dirt);
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

void Level::draw(sf::RenderWindow &window)
{
    window.draw(background);

    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));

    sf::View view = window.getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    int startX = std::max(0, static_cast<int>((center.x - size.x / 2) / tileSize));
    int startY = std::max(0, static_cast<int>((center.y - size.y / 2) / tileSize));
    int endX = std::min(gridWidth, static_cast<int>((center.x + size.x / 2) / tileSize) + 1);
    int endY = std::min(gridHeight, static_cast<int>((center.y + size.y / 2) / tileSize) + 1);

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
                continue; // Don't draw empty space, let background show
            }

            tileShape.setPosition(x * tileSize, y * tileSize);
            window.draw(tileShape);
        }
    }
}

sf::Vector2f Level::getSize() const
{
    return size;
}
