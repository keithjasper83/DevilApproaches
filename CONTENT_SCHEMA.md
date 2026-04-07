# Content Schema

This document outlines the data structures used to define game entities.

## Rooms
Rooms are defined by their functional type. Currently, these are hardcoded via enums, but will eventually move to an external data-driven format (e.g., JSON/YAML).

### `Room` Structure
```cpp
struct Room {
    int id;               // Unique identifier for a built room instance
    RoomType type;        // The functional category (e.g., Production, Training)
    int capacity;         // How many units or resources the room can hold
    int currentOccupancy; // Current number of units/resources in the room
};
```

### Supported `RoomType` Values
- `None`: Default state indicating no room.
- `Production`: Room designated for resource generation or crafting.
- `Training`: Room designated for unit progression and skill improvement.
- `Research`: Room designated for unlocking new technologies or spells.
