# Architecture

## Current Architecture
- **GameManager**: Orchestrates the main game loop.
- **WindowManager**: Manages SFML window creation, clearing, and displaying, as well as text rendering.
- **ControlManager**: Static class handling keyboard and controller inputs.
- **Level**: Grid-based tile map managing physical constraints (`TileType`: SolidRock, Dirt, Empty), territorial ownership (`Faction`: Neutral, Player, Enemy1), and room placement (`RoomType`). Includes interactions like digging, claiming territory, and building rooms. Dynamically renders tiles based on state, ownership, and room type.
- **Room**: Defines the structural properties of built facilities (`Production`, `Training`, `Research`) including occupancy and capacity.
- **Economy**: Manages balances and storage capacities for the multi-resource system (`Ore`, `Essence`, `Influence`).
- **Player**: Represents the physical or camera-based entity in the world; now holds a personal `Economy` instance.
- **AIPlayer**: Acts as an opponent logic controller. Periodically scans the level state and makes strategic decisions (claiming territory, building rooms) using its own `Economy`.
- **Unit**: Autonomous agents with needs (`morale`), jobs (`JobType`), combat stats (`hp`, `attackDamage`, `attackCooldown`, `attackRange`), and faction alignments. They are managed and updated by the `Level`.
- **Combat & Projectiles**: Handled within `Level::updateUnits` and `Level::updateProjectiles`. Combat utilizes a transient 2D spatial partitioning grid to quickly evaluate nearby enemies instead of an O(N^2) loop. Ranged units (`Ranger`) spawn `Projectile` entities which also evaluate hits against the spatial grid.
