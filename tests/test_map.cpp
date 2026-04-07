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

    std::cout << "Test Passed: Map and Digging Mechanics are correct." << std::endl;
    return 0;
}
