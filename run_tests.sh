#!/bin/bash
g++ -o test_player tests/test_player.cpp Player.cpp Level.cpp Economy.cpp Unit.cpp -I.
if [ $? -eq 0 ]; then
    ./test_player || exit 1
    rm test_player
else
    echo "test_player compilation failed"
    exit 1
fi

g++ -o test_map tests/test_map.cpp Level.cpp Room.cpp Unit.cpp -I.
if [ $? -eq 0 ]; then
    ./test_map || exit 1
    rm test_map
else
    echo "test_map compilation failed"
    exit 1
fi

g++ -o test_economy tests/test_economy.cpp Economy.cpp -I.
if [ $? -eq 0 ]; then
    ./test_economy || exit 1
    rm test_economy
else
    echo "test_economy compilation failed"
    exit 1
fi

g++ -o test_unit tests/test_unit.cpp Unit.cpp -I.
if [ $? -eq 0 ]; then
    ./test_unit || exit 1
    rm test_unit
else
    echo "test_unit compilation failed"
    exit 1
fi

g++ -o test_combat tests/test_combat.cpp Unit.cpp Level.cpp Room.cpp Projectile.cpp -I.
if [ $? -eq 0 ]; then
    ./test_combat || exit 1
    rm test_combat
else
    echo "test_combat compilation failed"
    exit 1
fi
