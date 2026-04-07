#pragma once
#include <map>

enum class ResourceType
{
    Ore,
    Essence,
    Influence
};

class Economy
{
public:
    Economy();

    // Modifiers
    void addResource(ResourceType type, int amount);
    bool spendResource(ResourceType type, int amount);

    // Getters / Setters
    int getResource(ResourceType type) const;
    void setCapacity(ResourceType type, int amount);
    int getCapacity(ResourceType type) const;

private:
    std::map<ResourceType, int> balances;
    std::map<ResourceType, int> capacities;
};
