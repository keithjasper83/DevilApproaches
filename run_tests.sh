#!/bin/bash
g++ -o test_player tests/test_player.cpp Player.cpp Level.cpp -I. -Itests/mocks
if [ $? -eq 0 ]; then
    ./test_player
    rm test_player
else
    echo "Compilation failed"
    exit 1
fi
