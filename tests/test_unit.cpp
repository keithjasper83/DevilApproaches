#include "Unit.h"
#include <iostream>

int main() {
    // Test Unit Initialization
    Unit worker(1, UnitType::Worker, 100.0f, 150.0f, 1); // 1 = Faction::Player

    if (worker.getId() != 1) {
        std::cerr << "Test Failed: Unit ID is incorrect." << std::endl;
        return 1;
    }

    if (worker.getType() != UnitType::Worker) {
        std::cerr << "Test Failed: Unit type is incorrect." << std::endl;
        return 1;
    }

    if (worker.getPosition().x != 100.0f || worker.getPosition().y != 150.0f) {
        std::cerr << "Test Failed: Unit position is incorrect." << std::endl;
        return 1;
    }

    if (worker.getFaction() != 1) {
        std::cerr << "Test Failed: Unit faction is incorrect." << std::endl;
        return 1;
    }

    if (worker.getCurrentJob() != JobType::Idle) {
        std::cerr << "Test Failed: Initial job should be Idle." << std::endl;
        return 1;
    }

    if (worker.getMorale() != 100) {
        std::cerr << "Test Failed: Initial morale should be 100." << std::endl;
        return 1;
    }

    // Test Job Modification
    worker.setJob(JobType::Digging);
    if (worker.getCurrentJob() != JobType::Digging) {
        std::cerr << "Test Failed: Job modification failed." << std::endl;
        return 1;
    }

    // Test Morale Modification and Clamping
    worker.modifyMorale(-50);
    if (worker.getMorale() != 50) {
        std::cerr << "Test Failed: Morale subtraction failed." << std::endl;
        return 1;
    }

    worker.modifyMorale(-100);
    if (worker.getMorale() != 0) {
        std::cerr << "Test Failed: Morale was not clamped to 0." << std::endl;
        return 1;
    }

    worker.modifyMorale(200);
    if (worker.getMorale() != 100) {
        std::cerr << "Test Failed: Morale was not clamped to 100." << std::endl;
        return 1;
    }

    std::cout << "Test Passed: Unit mechanics are correct." << std::endl;
    return 0;
}
