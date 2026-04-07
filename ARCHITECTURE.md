# Architecture

## Current Architecture
- **GameManager**: Orchestrates the main game loop.
- **WindowManager**: Manages SFML window creation, clearing, and displaying, as well as text rendering.
- **ControlManager**: Static class handling keyboard and controller inputs.
- **Level**: Grid-based tile map managing physical constraints (`TileType`: SolidRock, Dirt, Empty) and territorial ownership (`Faction`: Neutral, Player, Enemy1). Includes interactions like digging and claiming territory, and dynamically renders tiles based on state and ownership.
- **Player**: A basic entity with position and movement logic.
