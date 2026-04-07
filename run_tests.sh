#!/bin/bash
g++ -o test_player tests/test_player.cpp Player.cpp Level.cpp Economy.cpp -I.
if [ $? -eq 0 ]; then
    ./test_player
    rm test_player
else
    echo "test_player compilation failed"
    exit 1
fi

g++ -o test_map tests/test_map.cpp Level.cpp Room.cpp -I.
if [ $? -eq 0 ]; then
    ./test_map
    rm test_map
else
    echo "test_map compilation failed"
    exit 1
fi

g++ -o test_economy tests/test_economy.cpp Economy.cpp -I.
if [ $? -eq 0 ]; then
    ./test_economy
    rm test_economy
else
    echo "test_economy compilation failed"
    exit 1
fi
