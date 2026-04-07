# Changelog

## [Unreleased]
- Initial creation of repository audit.
- Refactored `Level` to a grid-based tile map system.
- Introduced `TileType` enum (`SolidRock`, `Dirt`, `Empty`).
- Implemented `Level::dig` to modify tile states in the game world.
- Implemented rendering logic for the tile grid in `Level::draw`.
- Added `test_map.cpp` to the test suite and updated `run_tests.sh`.
- Introduced `Faction` enum (`Neutral`, `Player`, `Enemy1`) to represent ownership domains.
- Implemented `Level::claimTile` to assign ownership.
- Updated `Level::draw` to overlay faction-colored squares on claimed tiles.
- Added tile claiming unit tests to `tests/test_map.cpp`.
- Introduced `RoomType` enum and `Room` struct in `Room.h` and `Room.cpp`.
- Extended `Level` class to support a `roomGrid` mapping.
- Implemented `Level::buildRoom` enforcing that rooms can only be built on empty, player-claimed tiles.
- Updated `Level::draw` to render rooms with specific colors layered over the grid.
- Added room placement unit tests in `tests/test_map.cpp` and updated `run_tests.sh`.
- Created `CONTENT_SCHEMA.md` to document data structures.
- Introduced `Economy` class and `ResourceType` enum (`Ore`, `Essence`, `Influence`).
- Added capacity and balance tracking to `Economy`.
- Integrated `Economy` into the `Player` class.
- Updated `Level::dig` to return a success boolean.
- Added unit tests for economy mechanics in `tests/test_economy.cpp`.
