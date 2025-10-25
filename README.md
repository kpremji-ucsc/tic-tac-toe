# Tic-Tac-Toe Game Implementation

## Overview
In this assignment, I implemented the TicTacToe.cpp file to finish the Tic-Tac-Toe game. I won't explain how tic-tac-toe works because I'm sure whoever is reading this doesn't need me to :)

## Implementation Details
All the implemented functions are listed here:
- `setUpBoard()`
- `actionForEmptyHolder()`
- `checkForWinner()`
- `checkForDraw()`
- `ownerAt()`
- `stopGame()`
- `stateString()` / `setStateString()`


#### Board Setup (`setUpBoard()`)
- Initializes 2 players for the game
- Configures a 3x3 game board
- Places 9 square images in the corresponding spots
- Calls `startGame()` to initialize the game state

#### Move Placement (`actionForEmptyHolder()`)
- Verifies that the holder is not null and is empty
- Gets the current player and creates their piece (X or O)
- Positions the piece at the holder's location
- Checks for endgame conditions after each move
- Ends the turn and moves on to the next player

#### Win Conditions (`checkForWinner()`)
- Checks all the winning combinations
- Returns the winning player or nullptr if no winner

#### Draw Detection (`checkForDraw()`)
- Checks if all 9 squares are filled, continues if true
- If there isn't a winner the game ends in a draw

#### Game State String Stuff
- `stateString()`: Converts board state to a 9-character string
- `setStateString()`: Recreates the board from the state string

#### Memory Management (`stopGame()`)
- Destroys all Bit objects on the board


### Development Environment
- **OS**: Windows 10
- **IDE**: Visual Studio Code
- **Compiler**: C++
- **Build System**: CMake 3.5.0+ (as listed in the CMakeLists.txt file)
- **UI Library**: ImGui

# AI Immplementation Update

## Overview
The assignment tasked me with creating an AI that will play the game against the player, and uses the negamax algorithm to determine its best moves. Although explained in the video that this algorithm may not be the most efficient, and will have repeat patterns, it would serve the purpose of the game and the assignment.

## Implementation Details
All the implemented functions are listed here:
- `updateAI()`
- `negamax()`
- `evaluateBoard()`
- `checkWinnerInBoard()`
- `isBoardFullArray()`
- `findBestMove()`
- `countEmptySquares()`

### AI Move (`updateAI()`)
- Calls `findBestMove()` to determine the best move
- Places the piece at the best move location
- Ends the turn and moves on to the next player

### Negamax Algorithm (`negamax()`)
- Recursively evaluates all possible moves
- Determines the best move based on a score
- Returns the score for the current board state

### Board Evaluation (`evaluateBoard()`)
- Checks for a winner and returns a score based on the outcome
- Returns 0 if tie game

### Winner Check (`checkWinnerInBoard()`)
- Checks all winning combinations
- Returns the winning player or 0 if no winner

### Board Full Check (`isBoardFullArray()`)
- Returns true if all 9 squares are filled, false otherwise

### Best Move (`findBestMove()`)
- Calls `negamax()` to evaluate all possible moves
- Returns the index of the best move

### Empty Square Count (`countEmptySquares()`)
- Counts the number of empty squares on the board lol





