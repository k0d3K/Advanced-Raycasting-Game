# Advanced Raycasting Game

This project is the **evolution of the original 42 project [cub3D]**, reimagined with advanced features and real 3D mechanics.
It goes far beyond a basic 2D raycasting engine by implementing **true 3D raycasting, multiple levels, real physics, and improved rendering algorithms**.


## Features

* **Advanced 3D Raycasting**: An upgraded rendering engine that supports multiple levels and more complex environments.
* **Paint Algorithm Integration**: Ensures smooth and accurate wall/floor/ceiling rendering.
* **Real Physics**:
  * Collision based on **3D capsule models** for both players and enemies.
  * More natural and immersive movement mechanics like jumps.
* **Multi-Level Support**: Explore beyond flat maps—dive into true multi-level 3D environments.

## Requirements

Before compiling and running the project, make sure you have:

* `make` utility
* `python3`

## Usage

Simply compile with:

```bash
make
```

To launch the game, run:

```bash
./raycast_game maps/adv1.adv
```
Once launched, select a level and start exploring.

Controles:
* Use 'WASD' to move yourself.
* Use the mouse to move your vision.
* Left clic to shoot.
* Press 'R' Reload.
* Press 'E' to open a door.
* Quit anytime with **ESC**.


Your goal is to collect all the coins and kill all the monster so you can finaly open the exit door.

Good luck and have fun exploring the maps and testing the engine!

You can also try running with another map:

```bash
./raycast_game maps/maze.cub
```