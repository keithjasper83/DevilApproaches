#!/bin/bash
g++ -o test_player tests/test_player.cpp Player.cpp Level.cpp -I.
if [ $? -eq 0 ]; then
    ./test_player
    rm test_player
else
    echo "test_player compilation failed"
    exit 1
fi

g++ -o test_map tests/test_map.cpp Level.cpp -I.
if [ $? -eq 0 ]; then
    ./test_map
    rm test_map
else
    echo "test_map compilation failed"
    exit 1
fi
