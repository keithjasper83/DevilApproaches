# Changelog

## [Unreleased]
- Initial creation of repository audit.
- Refactored `Level` to a grid-based tile map system.
- Introduced `TileType` enum (`SolidRock`, `Dirt`, `Empty`).
- Implemented `Level::dig` to modify tile states in the game world.
- Implemented rendering logic for the tile grid in `Level::draw`.
- Added `test_map.cpp` to the test suite and updated `run_tests.sh`.
