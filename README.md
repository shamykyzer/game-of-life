# Conway's Game of Life with raylib

A graphical C++ implementation of Conway's Game of Life using [raylib](https://www.raylib.com/).

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Conway's Game of Life is a cellular automaton devised by mathematician John Horton Conway. It consists of a grid of cells that evolve through generations based on simple rules, leading to complex and often beautiful patterns.

This project implements the Game of Life using C++ and **raylib** for graphical rendering, providing an interactive and visually appealing experience.

## Features

- Random initial state generation
- Graphical display using **raylib**
- Adjustable grid size and cell size
- Interactive controls for pausing, adjusting speed, and resetting
- Ability to toggle individual cells by clicking
- Cross-platform compatibility

## Requirements

- C++17 compatible compiler (e.g., g++ 7 or higher)
- **raylib** installed
- Make build system

## Installation

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
