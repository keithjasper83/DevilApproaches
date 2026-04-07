#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class TileType
{
    SolidRock,
    Dirt,
    Empty
};

class Level
{
  public:
    Level(float width, float height);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getSize() const;

    // Tile management
    void setTile(int x, int y, TileType type);
    TileType getTile(int x, int y) const;
    void dig(float worldX, float worldY); // Digs at world coordinates

    const float tileSize = 40.0f; // Each tile is 40x40 pixels

  private:
    sf::RectangleShape background;
    sf::Vector2f size = sf::Vector2f(4000, 4000);

    int gridWidth;
    int gridHeight;
    std::vector<TileType> grid;
};
