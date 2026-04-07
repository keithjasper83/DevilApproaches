#include "Economy.h"
#include <algorithm>

Economy::Economy()
{
    // Initialize default balances and capacities
    balances[ResourceType::Ore] = 0;
    balances[ResourceType::Essence] = 0;
    balances[ResourceType::Influence] = 0;

    capacities[ResourceType::Ore] = 1000;
    capacities[ResourceType::Essence] = 500;
    capacities[ResourceType::Influence] = 100;
}

void Economy::addResource(ResourceType type, int amount)
{
    if (amount <= 0) return;

    int newBalance = balances[type] + amount;
    balances[type] = std::min(newBalance, capacities[type]);
}

bool Economy::spendResource(ResourceType type, int amount)
{
    if (amount <= 0) return false;

    if (balances[type] >= amount)
    {
        balances[type] -= amount;
        return true;
    }
    return false; // Insufficient funds
}

int Economy::getResource(ResourceType type) const
{
    auto it = balances.find(type);
    if (it != balances.end()) {
        return it->second;
    }
    return 0;
}

void Economy::setCapacity(ResourceType type, int amount)
{
    if (amount < 0) return;
    capacities[type] = amount;

    // Clamp current balance if capacity is lowered
    if (balances[type] > capacities[type])
    {
        balances[type] = capacities[type];
    }
}

int Economy::getCapacity(ResourceType type) const
{
    auto it = capacities.find(type);
    if (it != capacities.end()) {
        return it->second;
    }
    return 0;
}
