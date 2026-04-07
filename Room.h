#pragma once

enum class RoomType
{
    None,
    Production,
    Training,
    Research
};

struct Room
{
    int id;
    RoomType type;
    int capacity;
    int currentOccupancy;

    Room(int id = 0, RoomType type = RoomType::None)
        : id(id), type(type), capacity(0), currentOccupancy(0) {}
};
