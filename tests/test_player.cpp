#include "Player.h"
#include "Level.h"
#include <iostream>
#include <cassert>

int main() {
    // 1. Initialize a Level with specific dimensions
    Level level(800.f, 600.f);

    // 2. Create a Player associated with that level
    Player player(level);

    // 3. Call setStartPosition()
    player.setStartPosition();

    // 4. Assert that getPosition() returns a position equal to half the level's width and height
    sf::Vector2f pos = player.getPosition();

    std::cout << "Player position: (" << pos.x << ", " << pos.y << ")" << std::endl;

    if (pos.x == 400.f && pos.y == 300.f) {
        std::cout << "Test Passed: Player start position is correct." << std::endl;
        return 0;
    } else {
        std::cerr << "Test Failed: Player start position is incorrect!" << std::endl;
        return 1;
    }
}
