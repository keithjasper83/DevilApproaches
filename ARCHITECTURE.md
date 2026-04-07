# Architecture

## Current Architecture
- **GameManager**: Orchestrates the main game loop.
- **WindowManager**: Manages SFML window creation, clearing, and displaying, as well as text rendering.
- **ControlManager**: Static class handling keyboard and controller inputs.
- **Level**: Grid-based tile map managing `TileType` (SolidRock, Dirt, Empty) and interactions like digging. Includes dynamic rendering of tiles based on their state.
- **Player**: A basic entity with position and movement logic.
