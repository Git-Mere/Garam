# Garam

A 2D action-platformer with four boss fights, an inventory system, and multi-zone progression, built from scratch in C++ for a DigiPen game programming course.

![C++](https://img.shields.io/badge/language-C%2B%2B-blue) ![SFML](https://img.shields.io/badge/SFML-2.5.1-green)

## Features

- **Four distinct boss encounters** — each with unique movement and attack patterns (dash, energy throw, fireball, teleport, worm dive)
- **Multi-zone progression** — forest, cave, and volcano stages with zone-specific enemies and backgrounds
- **Inventory and crafting system** — collect items, combine ingredients using a recipe table, and equip gear
- **Dual-weapon mechanics** — switch between melee and ranged (cane / charm) mid-combat
- **Full animation pipeline** — custom sprite sheet (`.spt`) and animation (`.anm`) format with idle, run, jump, dash, attack, and stun states

## Demo

![screenshot](./screenshot.png)

## Built With

- **C++** — all game systems implemented from scratch: physics, collision, camera, state machines, animation
- **SFML 2.5.1** — window management, 2D rendering, and audio playback; bundled under `Lib/` so no external install is required
- **GLSL** — shader effects applied to in-game visuals
- **CMake** — cross-platform build definition alongside the Visual Studio solution
- **Visual Studio** — primary IDE used during development

## Getting Started

### Prerequisites

- Windows (project targets MSVC; DLLs are pre-built for Win32/Win64)
- Visual Studio 2019 or later

### Installation

```bat
git clone https://github.com/Git-Mere/Garam.git
cd Garam
```

Open the solution file in Visual Studio:

```
Gam_150_project/Gam_150_project.sln
```

### Build & Run

1. Select the desired configuration (`Debug` or `Release`) in Visual Studio.
2. Press **Ctrl + Shift + B** to build.
3. Press **F5** to run. The SFML DLLs in the project directory are loaded automatically.

> **Note:** The pre-built SFML 2.5.1 binaries for both debug and release are located under `Lib/SFML-2.5.1/bin/`.

## What I Learned

**Designing boss AI without an engine's state machine**
Each of the four bosses needed distinct behaviour (Boss1 dashes toward the player, Boss3 teleports and alternates between fireball and magic patterns, Boss4 submerges and re-emerges). Without a ready-made FSM, I structured each boss as an explicit enum-driven state machine in its own `.cpp` file. The challenge was keeping transition logic readable while preventing states from bleeding into one another — for example, Boss2's `back_attack` → `fall_attack` → `idle` chain required careful timer management to avoid skipping frames when the attack animation ended early.

**Building a sprite and animation system from scratch**
SFML provides texture loading and drawing, but not sprite-sheet slicing or frame-based playback. I defined a custom `.spt` format for describing sprite regions and a `.anm` format for sequencing frames with per-frame durations. Implementing this taught me how animation data and render state must stay decoupled: the `animation` module advances frames on a timer, while `sprite` handles only UV mapping and draw calls.

**Inventory and crafting data layout**
The item system has several dozen items and a recipe table (`ItemTable.h`, `recipe.txt`). Keeping item definitions in a flat table and resolving crafting results at runtime (rather than hard-coding them in game logic) made adding new recipes straightforward and separated data from behaviour — a pattern I carried into later projects.

## License

No license is specified for this repository. All rights reserved by the original authors.