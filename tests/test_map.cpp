#include "Level.h"
#include <iostream>
#include <cassert>

int main() {
    // 1. Initialize a Level with specific dimensions
    Level level(800.f, 600.f);

    // 2. Verify initial grid dimensions
    // 800 / 40 = 20
    // 600 / 40 = 15
    sf::Vector2f size = level.getSize();
    if (size.x != 800.f || size.y != 600.f) {
        std::cerr << "Test Failed: Level size is incorrect!" << std::endl;
        return 1;
    }

    // 3. Verify initial tile states (all should be Dirt)
    if (level.getTile(0, 0) != TileType::Dirt) {
        std::cerr << "Test Failed: Initial tile is not Dirt!" << std::endl;
        return 1;
    }

    // 4. Test digging (world coordinates)
    level.dig(20.f, 20.f); // Should hit tile (0, 0)
    if (level.getTile(0, 0) != TileType::Empty) {
        std::cerr << "Test Failed: Tile did not change to Empty after digging!" << std::endl;
        return 1;
    }

    // 5. Verify adjacent tile remains Dirt
    if (level.getTile(1, 0) != TileType::Dirt) {
        std::cerr << "Test Failed: Adjacent tile unexpectedly changed!" << std::endl;
        return 1;
    }

    // 6. Test out-of-bounds safety
    if (level.getTile(100, 100) != TileType::SolidRock) {
        std::cerr << "Test Failed: Out of bounds tile did not return SolidRock!" << std::endl;
        return 1;
    }

    // 7. Verify initial tile ownership (all should be Neutral)
    if (level.getTileFaction(0, 0) != Faction::Neutral) {
        std::cerr << "Test Failed: Initial tile ownership is not Neutral!" << std::endl;
        return 1;
    }

    // 8. Test claiming a tile
    // We already dug tile (0, 0), so it's Empty. Let's claim it.
    level.claimTile(0, 0, Faction::Player);
    if (level.getTileFaction(0, 0) != Faction::Player) {
        std::cerr << "Test Failed: Tile was not correctly claimed by Player!" << std::endl;
        return 1;
    }

    // 9. Test claiming a dirt tile
    level.claimTile(1, 0, Faction::Enemy1);
    if (level.getTileFaction(1, 0) != Faction::Enemy1) {
        std::cerr << "Test Failed: Dirt tile was not correctly claimed by Enemy1!" << std::endl;
        return 1;
    }

    // 10. Test claiming an out-of-bounds / solid rock tile (should remain neutral)
    level.claimTile(100, 100, Faction::Player);
    if (level.getTileFaction(100, 100) != Faction::Neutral) {
        std::cerr << "Test Failed: Out of bounds tile somehow acquired an ownership state!" << std::endl;
        return 1;
    }

    std::cout << "Test Passed: Map, Digging, and Claiming Mechanics are correct." << std::endl;
    return 0;
}
