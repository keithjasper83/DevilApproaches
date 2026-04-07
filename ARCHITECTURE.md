# Architecture

## Current Architecture
- **GameManager**: Orchestrates the main game loop.
- **WindowManager**: Manages SFML window creation, clearing, and displaying, as well as text rendering.
- **ControlManager**: Static class handling keyboard and controller inputs.
- **Level**: Grid-based tile map managing physical constraints (`TileType`: SolidRock, Dirt, Empty), territorial ownership (`Faction`: Neutral, Player, Enemy1), and room placement (`RoomType`). Includes interactions like digging, claiming territory, and building rooms. Dynamically renders tiles based on state, ownership, and room type.
- **Room**: Defines the structural properties of built facilities (`Production`, `Training`, `Research`) including occupancy and capacity.
- **Player**: A basic entity with position and movement logic.
