#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Room.h"

enum class TileType
{
    SolidRock,
    Dirt,
    Empty
};

enum class Faction
{
    Neutral,
    Player,
    Enemy1
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

    // Ownership management
    void claimTile(int x, int y, Faction faction);
    Faction getTileFaction(int x, int y) const;

    // Room management
    void buildRoom(int x, int y, RoomType type);
    RoomType getRoom(int x, int y) const;

    const float tileSize = 40.0f; // Each tile is 40x40 pixels

  private:
    sf::RectangleShape background;
    sf::Vector2f size = sf::Vector2f(4000, 4000);

    int gridWidth;
    int gridHeight;
    std::vector<TileType> grid;
    std::vector<Faction> ownershipGrid;
    std::vector<RoomType> roomGrid;
};
