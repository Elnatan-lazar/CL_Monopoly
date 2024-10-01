# Monopoly Game Project

This project is a C++ implementation of a Monopoly-like game with a graphical interface using SFML (Simple and Fast Multimedia Library). It was developed as a university project and provides a basic simulation of the classic Monopoly game, including players, properties, dice rolls, and game actions.

## Project Overview

The project is divided into multiple C++ classes, each representing a specific aspect of the Monopoly game. These classes work together to simulate the game's logic, manage player actions, handle property ownership, and display the game interface using SFML.

### Classes Overview

#### 1. `Card.cpp`
- **Purpose**: Manages the Chance and Community Chest cards.
- **Details**: This file contains methods to draw a random card from the deck and handle card actions that affect the player (e.g., paying money, advancing to a specific location, drawing a 'Get Out of Jail Free' card).
- **Functions:**
  - `Card::drawChanceCard()`: Draws a random chance card and returns it.
  - `Card::drawCommunityChestCard()`: Draws a random community chest card and returns it.

#### 2. `Dice.cpp`
- **Purpose**: Handles the logic for dice rolls.
- **Details**: This class simulates the rolling of two dice and includes functionality to check if the player has rolled a double, which is crucial for handling cases like getting out of jail or rolling three consecutive doubles.
- **Functions:**
  - `Dice::roll()`: Rolls two dice and updates the dice values.
  - `Dice::isDouble()`: Checks if both dice rolled the same value (a double).

#### 3. `Location.cpp`
- **Purpose**: Represents properties or other types of locations on the game board.
- **Details**: This file defines different types of locations (e.g., properties, utilities, railroads) with attributes like cost, rent, and ownership. It handles buying, selling, and building houses/hotels on properties.
- **Functions:**
  - `Location::buyHouse()`: Allows a house to be built on the property if the player meets the requirements.
  - `Location::reset()`: Resets the property to its original state if sold or mortgaged.

#### 4. `Player.cpp`

- **Purpose**: Represents a player in the game.
- **Details**: The `Player` class maintains player-specific data such as balance, properties owned, current position on the board, jail status, and the number of 'Get Out of Jail Free' cards. It includes methods to update the player’s cash, properties, and status in the game.

#### 5. `Board.cpp`
- **Purpose**:  Manages the game board's layout, drawing the board on the screen, and updating property states.
- **Details**: This file contains the `Board` class, which initializes the game board with all properties, utilities, and special squares (like 'Go', 'Jail', 'Chance', etc.). It also manages the display of the board using SFML, including updating property ownership visuals (e.g., houses/hotels).
- - **Functions:**
  - `Board::draw(sf::RenderWindow &window)`: Draws the Monopoly board on the window.
  - `Board::drawPlayerMarkers(sf::RenderWindow &window, const std::vector<Player> &players)`: Draws the players' tokens on their respective positions.


#### 6. `action.cpp`
- Handles player actions related to purchasing and selling properties, building houses, and upgrading properties to hotels.
- **Purpose**: Contains functions for player actions during the game.
- **Details**: This file implements functions that handle player actions, such as buying houses/hotels, selling properties, and paying rent when landing on another player’s property. It also includes the logic for handling menu interactions.
- **Functions:**
- `buyHouse(Player &player, sf::RenderWindow &window, sf::Font &font)`: Allows a player to buy a house or hotel if they meet the game conditions.
- `sellProperty(Player &player, sf::RenderWindow &window, sf::Font &font)`: Opens the sell menu, enabling a player to sell their properties.


#### 7. `maingame.cpp`
- **Purpose**: Contains the core game loop and manages the overall gameplay.
- **Details**: This file implements the `mainGame` function, which serves as the main game loop, handling player turns, dice rolls, and interactions with the game board. It manages updating the game state, displaying messages, and transitioning between players’ turns.
- **Function**
- `mainGame(sf::RenderWindow &window, sf::Font &font)`: The primary game loop where player turns, dice rolls, and game actions are processed.


#### 8. `playerManu.cpp`
- **Purpose**: Manages the player interaction menu.
- **Details**: Contains the logic for displaying the player's properties and allowing the player to perform actions such as selling properties. It provides a graphical interface for the player to interact with their assets.
- **Function**
  - `Player::move(int steps, Board &gameBoard)`: Moves the player across the board based on the dice roll.
  - `Player::updateCashInHand(int amount)`: Adjusts the player's cash balance.

#### 9. `definitions.cpp`
- **Purpose**: Defines global constants and utility functions.
- **Details**: This file includes common constants, utility functions, and helper definitions used across different parts of the project to ensure consistent behavior and values.

#### 10. `main.cpp`
- **Purpose**: Entry point of the program.
- **Details**: This file initializes the game window and begins the main game loop by calling the `mainGame` function from `maingame.cpp`.

### How to Run the Project

1. **Requirements**:
   - Install [SFML 2.6.1](https://www.sfml-dev.org/download.php) and ensure your environment is set up correctly.
   - A C++ compiler such as g++ or the MinGW toolchain on Windows.
   - CMake for building the project.

2. **Building the Project**:
   - Clone the repository:
     ```
     git clone https://github.com/your-username/monopoly-project.git
     ```
   - Navigate to the project directory:
     ```
     cd monopoly-project
     ```
   - Build the project using CMake:
     ```
     mkdir build && cd build
     cmake ..
     make
     ```
   - Run the executable:
     ```
     ./MonopolyGame
     ```

### Game Controls

- Use the graphical interface to roll dice, buy/sell properties, build houses/hotels, and manage player turns.
- The sidebar displays information about the current player, and buttons are provided for actions like rolling dice, ending a turn, buying/selling properties, etc.

### Project Structure

<pre>
MonopolyGame/
│
├── src/
│   ├── action.cpp
│   ├── Board.cpp
│   ├── Card.cpp
│   ├── definitions.cpp
│   ├── Dice.cpp
│   ├── Location.cpp
│   ├── main.cpp
│   ├── maingame.cpp
│   ├── Player.cpp
│   ├── playerManu.cpp
│
├── include/        (Header files for each corresponding .cpp file)
├── assets/         (Fonts, images, and other game assets)
├── CMakeLists.txt  (Build configuration file)
└── README.md
</pre>

### video and pics
[![Monopoly Game Demo](https://img.youtube.com/vi/AgjTRFQBAOs/0.jpg)](https://www.youtube.com/watch?v=AgjTRFQBAOs)

![Monopoly Game Demo](https://raw.githubusercontent.com/Elnatan-lazar/CL_Monopoly/refs/heads/master/open%20screen.jpg)

![Monopoly Game Demo](https://github.com/Elnatan-lazar/CL_Monopoly/blob/master/set%20player%20order.jpg?raw=true)

![Monopoly Game Demo](https://github.com/Elnatan-lazar/CL_Monopoly/blob/master/board%20game.jpg?raw=true)

