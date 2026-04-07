#include "Economy.h"
#include <iostream>

int main() {
    Economy economy;

    // Test initial setup
    if (economy.getResource(ResourceType::Ore) != 0) {
        std::cerr << "Test Failed: Initial Ore balance should be 0." << std::endl;
        return 1;
    }

    // Test capacity bounds
    economy.addResource(ResourceType::Ore, 2000);
    if (economy.getResource(ResourceType::Ore) != economy.getCapacity(ResourceType::Ore)) {
        std::cerr << "Test Failed: Ore balance exceeded capacity." << std::endl;
        return 1;
    }

    // Test spending
    if (economy.spendResource(ResourceType::Ore, 500) == false) {
        std::cerr << "Test Failed: Should be able to spend 500 Ore." << std::endl;
        return 1;
    }

    if (economy.getResource(ResourceType::Ore) != 500) {
        std::cerr << "Test Failed: Ore balance after spending is incorrect." << std::endl;
        return 1;
    }

    // Test overspending
    if (economy.spendResource(ResourceType::Ore, 1000) == true) {
        std::cerr << "Test Failed: Should not be able to spend more than balance." << std::endl;
        return 1;
    }

    // Test dynamic capacity reduction
    economy.setCapacity(ResourceType::Ore, 100);
    if (economy.getResource(ResourceType::Ore) != 100) {
        std::cerr << "Test Failed: Balance was not clamped when capacity was reduced." << std::endl;
        return 1;
    }

    std::cout << "Test Passed: Economy mechanics are correct." << std::endl;
    return 0;
}
