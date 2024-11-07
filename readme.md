

# Gamers Database Manager

This project implements a console-based **Gamers Database Manager** that manages players and games using a **Binary Search Tree (BST)** for players and a **dynamic array** for games. The system includes various functionalities for managing data, querying, and displaying results based on provided commands.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Usage](#usage)
- [File Structure](#file-structure)
- [Functions and Modules](#functions-and-modules)
- [License](#license)

## Project Overview
The **Gamers Database Manager** is a database management system designed to handle a dataset of players and the games they play. The system uses a **Binary Search Tree (BST)** to store player data and supports operations such as insertion, deletion, search, and retrieval.

This system was created as a programming project for understanding fundamental data structures, file handling, and memory management in C++.

## Features

The project implements the following features:

1. **Insertion**
   - Allows inserting new players and games into the system.
   - Prevents duplicate player or game IDs.
   
2. **Search and Retrieval**
   - Allows searching for players and games by their IDs.

3. **Deletion**
   - Deletes players from memory and ensures no memory leaks occur.

4. **Save Data**
   - Saves player data to a CSV file in Preorder Traversal format for easy restoration.

5. **Display N Layers**
   - Shows all entries up to N layers of the BST. If N exceeds the layers present, it displays a warning.

6. **Show Layer Number**
   - Shows the layer number (depth) of a specified player in the tree.

7. **Show Path**
   - Prints the path taken to locate a player in the tree.

8. **Edit Entry**
   - Allows editing a player's information. Repositions nodes in the BST if primary keys change.

9. **Top N Players**
   - Displays the top N players who play the most games.

10. **Show Details**
    - Displays the details of a specific player, along with all games played.

11. **Has Played**
    - Checks if a player has played a specific game with optimized search time.

## Getting Started

### Prerequisites
- **C++ Compiler**: Make sure you have a C++ compiler like `g++` installed.
- **Git** (optional): For version control if you're using GitHub.

### Installation
1. **Clone the Repository**:

   git clone https://github.com/AsgharAima/GamersDatabaseManager.git
   cd DS_B_A3_i212772

2. **Compile the Code**:
   
   g++ DS_B_A3_i212772.cpp -o run
   

3. **Add Data Files**:
   - Ensure you have `Players.txt` and `Games.txt` files in the same directory as `main.cpp`. These files should contain your initial dataset of players and games.

### Usage
Run the compiled executable:
./DS_B_A3_i212772


### Menu Options
Once you run the program, a menu will appear with the following options:

1. **Display All Games**: Lists all games in the system.
2. **Display All Players**: Shows all players in the BST up to 10 layers by default.
3. **Insert New Player**: Allows adding a new player with details.
4. **Insert New Game**: Allows adding a new game with details.
5. **Search Player**: Finds a player by ID and displays their info.
6. **Search Game**: Finds a game by ID and displays its info.
7. **Delete Player**: Deletes a player by ID.
8. **Save Data to File**: Saves all player data in Preorder Traversal format to `players_output.csv`.
9. **Show N Layers of Tree**: Displays players up to a specified number of layers.
10. **Show Layer Number of Player**: Shows the depth of a specific player in the BST.
11. **Show Path to Player**: Shows the path from the root to a specified player.
12. **Edit Player**: Allows editing a player’s details.
13. **Find Top N Players**: Displays the top N players who play the most games.
14. **Show Player Details**: Shows the details of a player and all games they have played.
15. **Check if Player Has Played a Specific Game**: Checks if a specified player has played a specified game.

## File Structure

```
DS_B_A3_i212772/
│
├── DS_B_A3_i212772.cpp            # Main C++ code for the project
├── Players.txt         # Initial dataset for players
├── Games.txt           # Initial dataset for games
├── players_output.csv  # File where data is saved in Preorder Traversal format
└── README.md           # Project documentation
```

## Functions and Modules

### Classes and Functions in `main.cpp`

- **Game**: Represents a game with attributes such as gameID, name, developer, publisher, rating, and downloads.
- **Player**: Represents a player with attributes such as playerID, name, phone, email, password, primaryGameID, and rating.
- **BST**: Binary Search Tree for managing players with functions for insertion, search, deletion, and retrieval.
  - **insert**: Adds a player to the BST.
  - **search**: Finds a player by ID.
  - **deletePlayer**: Deletes a player and manages memory.
  - **saveToFile**: Saves players to a CSV file in Preorder Traversal.
  - **showNLayers**: Displays players up to N layers.
  - **getLayerNumber**: Returns the layer number of a specific player.
  - **showPathToPlayer**: Shows the path to a player.
  - **displayTopNPlayers**: Displays the top N players based on the number of games.
- **GameList**: Dynamic array for managing games.
  - **addGame**: Adds a game to the array.
  - **searchGame**: Finds a game by ID.
  - **displayAllGames**: Shows all games in the system.

## License
This project is for educational purposes only and is not licensed for commerial use
