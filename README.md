# Kingdom Decision Game

A text-based resource management game written in C where you rule a kingdom and make decisions that affect your people, court, and treasury.

## Overview

You play as the ruler of a kingdom with three main resources:

- **People (`mardom`)**
- **Court (`darbar`)**
- **Treasury (`khazane`)**

Each turn, a random scenario is presented from a set of predefined choice files. You must choose between two options, each of which increases or decreases these resources in different ways. Your goal is to keep your kingdom stable for as long as possible.

The game supports **saving and loading** progress using a player-specific binary save file.

## Features

- **Text-based gameplay** entirely in the terminal.
- **Random event selection** from multiple scenario files listed in `CHOICES.txt`.
- **Two-choice decision system** for each scenario.
- **Three resource metrics**:
  - People (`mardom`)
  - Court (`darbar`)
  - Treasury (`khazane`)
- **Win/Lose conditions** based on resource values:
  - Game over if any resource drops to 0 or below.
  - Game over if the average of the three resources falls below 10.
- **Save and load system**:
  - Saves game state (resources and remaining choices) to a file named after the player.
  - Ability to resume an old game later.
