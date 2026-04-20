# So_long - 2D Game Engine

![So_long Screenshot](https://fankahou.com/assets/so_long_screen.jpg)

## 🎮 Play in Browser
* **[Click here to play the Standard Demo](https://fankahou.com/so_long_web/)**

* **[Click here for the 2P Multiplayer Mode](https://fankahou.com/so_long_web_2p/)**

*(Controls: WASD / Arrows to Move • Collect all items to escape!)*

---

## 📝 About the Project
**So_long** is a 2D top-down game built from scratch in C using the MiniLibX graphical library. The project serves as an introduction to basic graphics, window management, and event-driven programming.

The goal is for the player to collect all items on a map and reach the exit in the fewest moves possible, while avoiding obstacles or enemies.

## 🚀 Features
* **Custom Map Parsing:** Reads and validates `.ber` map files with strict error handling.
* **Sprite Rendering:** Efficient handling of textures for the player, walls, collectibles, and exits.
* **Pathfinding Validation:** Includes a flood-fill algorithm to ensure every map is solvable before the game begins.
* **Multiplayer Support:** An extended version featuring local 2P co-op/competitive play.
* **WebAssembly Port:** Fully playable in modern browsers via Emscripten and SDL2.

## 🛠️ Installation & Usage (Local)

### Prerequisites
* A Linux or Mac machine with `minilibx` installed.
* `gcc` and `make` utilities.

### Build
```bash
# Clone the repository
git clone [https://github.com/fankahou/so_long.git](https://github.com/fankahou/so_long.git)
cd so_long
```

### Build the game
```bash
make
```

### Run the game with a map
./so_long maps/1.ber

### 🗺️ Map Requirements
The game parses maps with the following components:

1: Wall

0: Empty Space

C: Collectible

E: Exit

P: Player Starting Position

# 📂 Specialized MLX Versions
For improved performance on modern hardware, check out these specialized MiniLibX versions:

* **Mac M1+ (Metal Support): [Multiplayer](https://github.com/fankahou/so_long_multiplayer_mac_m1$0)**

---

Created as part of the 42 Vienna curriculum.
