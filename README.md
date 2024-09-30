# Conway's Game of Life with raylib

A graphical C++ implementation of Conway's Game of Life using [raylib](https://www.raylib.com/).

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [How the Age-Based Coloring Works](#how-the-age-based-coloring-works)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Conway's Game of Life is a cellular automaton devised by mathematician John Horton Conway. It consists of a grid of cells that evolve through generations based on simple rules, leading to complex and often beautiful patterns.

This project implements the Game of Life using C++ and **raylib** for graphical rendering, providing an interactive and visually appealing experience. The latest update introduces age-based coloring of cells, enhancing the visual representation of the simulation.

_This project was inspired by my second-year module on Artificial Intelligence at the University of Leeds._

## Features

- **Random Initial State Generation**: Start with a randomly populated grid.
- **Graphical Display using raylib**: Smooth and efficient rendering of the grid.
- **Adjustable Grid and Cell Size**: Easily modify the dimensions to suit your preferences.
- **Interactive Controls**:
  - Pause and resume the simulation.
  - Adjust the simulation speed.
  - Reset to a new random state.
  - Toggle individual cells by clicking.
- **Age-Based Cell Coloring**: Cells change color as they age, transitioning from blue (young) to red (old), providing insights into the longevity and evolution of patterns.
- **Cross-Platform Compatibility**: Runs on Windows, macOS, and Linux.

## Requirements

- **C++17** compatible compiler (e.g., g++ 7 or higher)
- **raylib** (version 3.0 or higher)
- **Make** build system

## Installation

### Clone the Repository

```bash
git clone https://github.com/yourusername/game-of-life-raylib.git
cd game-of-life-raylib
```

### Install raylib

Follow the instructions on the [raylib website](https://www.raylib.com/) or see the setup steps in the [Setting Up raylib](#2-setting-up-raylib) section.

#### For Linux:

```bash
# Install dependencies
sudo apt-get install libasound2-dev libudev-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libgl1-mesa-dev

# Clone raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Compile raylib (static library)
make PLATFORM=PLATFORM_DESKTOP

# Install raylib
sudo make install
