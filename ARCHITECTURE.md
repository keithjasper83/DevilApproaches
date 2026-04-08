# Architecture

## Current Architecture
- **GameManager**: Orchestrates the main game loop.
- **WindowManager**: Manages SFML window creation, clearing, and displaying, as well as text rendering.
- **ControlManager**: Static class handling keyboard and controller inputs.
- **Level**: Grid-based tile map managing physical constraints (`TileType`: SolidRock, Dirt, Empty), territorial ownership (`Faction`: Neutral, Player, Enemy1), and room placement (`RoomType`). Includes interactions like digging, claiming territory, and building rooms. Dynamically renders tiles based on state, ownership, and room type.
- **Room**: Defines the structural properties of built facilities (`Production`, `Training`, `Research`) including occupancy and capacity.
- **Economy**: Manages balances and storage capacities for the multi-resource system (`Ore`, `Essence`, `Influence`).
- **Player**: Represents the physical or camera-based entity in the world; now holds a personal `Economy` instance.
- **Unit**: Autonomous agents with needs (`morale`), jobs (`JobType`), combat stats (`hp`, `attackDamage`), and faction alignments. They are managed, updated, and engage in simulated proximity combat via the `Level`.
