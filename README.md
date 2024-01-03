# WaTor OpenGL

## Overview

This project implements a Wa-Tor simulation using C and OpenGL for visualization. Wa-Tor is a simulation of a predator (sharks) and prey (fish) ecosystem in a 2D grid.

<img src="./images/wator.gif"  width="300" height="300">

## Prerequisites

Before running the simulation, ensure you have the following prerequisites installed:

- C compiler (e.g., gcc/clang etc)
- OpenGL library
- GLUT (OpenGL Utility Toolkit)
- CMake

## Build and Run

Follow these steps to build and run the simulation:

**Clone the Repository:**

```sh
git clone https://github.com/Unic-X/Wator-OpenGL.git

cd wator-simulation
```
**Make binary**

```sh
make
```
**Run Simulation**

```sh
./main
```

## Customization
Keys used for customizing state variables: 

* `Arrow Up` : Increase FPS 

* `Arrow Down`: Reduce FPS

* `A/D` : Decrease/Increase Spawn Rate of Sharks

* `S/W` : Decrease/Increase Spawn Rate of Sharks


## License

This project is licensed under the [MIT License](https://spdx.org/licenses/MIT.html). Feel free to contribute.