# SFCM2 - Simply Fast Circuit Maker 2

A simple, fast and cross-platform Circuit Maker 2 (Roblox) simulator written in C++ with SFML.

# Motivation

This program enables running something similar to Circuit Maker 2, but way more **faster** and **portable** (detached from Roblox). This project arrived from the necessity to play it on my FreeBSD platform, which can't run Roblox (at least not that I could work around). It main phylosophy is to be as simplistic as possible while correctly simulating what would work on Circuit Maker 2.

# Dependencies

- SFML 3.1

# Getting Started

## Build from source

In order to test this program, the current only way is to build it from source. To do so, follow these steps (adapt it to your terminal):

```bash
git clone https://www.github.com/Chard2512/SFCM2.git
cd SFCM2
mkdir build
cd build
cmake .. && make
```

This will fetch the repository from github and build the program to `build/bin/sfcm2`.

You can then run `sfcm2 --help` to check how to use it. `docs/examples/savestrings` provides some savestrings to run.

## Usage

To drag camera around, press and hold mouse right button.

To zoom in and out, scroll mouse wheel.

To interact with a block, position your cursor in the block you want to interact and press mouse left button.