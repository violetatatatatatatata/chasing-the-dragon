# Chasing the Dragon (cub3D)
*This project has been created as part of the 42 curriculum by Alex Alcaide and Violeta Velandria.*

![til](https://c.tenor.com/8L0fy2-EfzcAAAAC/tenor.gif)

## Description
**Chasing the Dragon** is a 3D game engine inspired by Wolfenstein 3D. Developed as the "cub3D" project within the 42 curriculum, its primary goal is to explore the principles of **Raycasting**—a technique used to create a 3D perspective from a 2D map.

The project implements:
* A first-person perspective using raycasting logic.
* Textured walls (North, South, East, West) and custom floor/ceiling colors.
* Smooth player movement and rotation.
* Dynamic sprite rendering, including a "Dragon" and animated player arms.
* A mini-map UI for navigation.
* The player speed is increased everytime he has a shot. When he is lack of shots, _he's slow af_. 
* _Press J for an easter egg._

## Instructions

### Prerequisites
To compile and run this project, you will need:
* A C compiler (e.g., `cc`).
* **MLX42** library dependencies (GLFW and CMake).
* The `make` utility.

### Compilation
Build the executable by running the following command in the root of the repository:
```bash
make
```
This will automatically compile the local libft and MLX42 libraries before generating the cub3D executable.

#### Execution
Run the game by providing a valid map file with the .cub extension as an argument:
```bash
./cub3D maps/basic.cub
```

#### Controls:
- W / A / S / D: Move the player.
- Left / Right Arrows: Rotate the camera.
- ESC: Close the game.

#### Resources
Documentation & Tutorials
- Lode's Raycasting Tutorial: A fundamental guide to understanding the mathematics behind raycasting.
- MLX42 Documentation: Official repository and documentation for the graphics library used.
