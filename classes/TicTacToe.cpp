#include "TicTacToe.h"

// -----------------------------------------------------------------------------
// TicTacToe.cpp
// -----------------------------------------------------------------------------
// This file is intentionally *full of comments* and gentle TODOs that guide you
// through wiring up a complete Tic‑Tac‑Toe implementation using the game engine’s
// Bit / BitHolder grid system.
//
// Rules recap:
//  - Two players place X / O on a 3x3 grid.
//  - Players take turns; you can only place into an empty square.
//  - First player to get three-in-a-row (row, column, or diagonal) wins.
//  - If all 9 squares are filled and nobody wins, it’s a draw.
//
// Notes about the provided engine types you'll use here:
//  - Bit              : a visual piece (sprite) that belongs to a Player
//  - BitHolder        : a square on the board that can hold at most one Bit
//  - Player           : the engine’s player object (you can ask who owns a Bit)
//  - Game options     : let the mouse know the grid is 3x3 (rowX, rowY)
//  - Helpers you’ll see used: setNumberOfPlayers, getPlayerAt, startGame, etc.
//
// I’ve already fully implemented PieceForPlayer() for you. Please leave that as‑is.
// The rest of the routines are written as “comment-first” TODOs for you to complete.
// -----------------------------------------------------------------------------

const int AI_PLAYER   = 1;      // index of the AI player (O)
const int HUMAN_PLAYER= 0;      // index of the human player (X)

TicTacToe::TicTacToe()
{
}

TicTacToe::~TicTacToe()
{
}

// -----------------------------------------------------------------------------
// make an X or an O
// -----------------------------------------------------------------------------
// DO NOT CHANGE: This returns a new Bit with the right texture and owner
Bit* TicTacToe::PieceForPlayer(const int playerNumber)
{
    // depending on playerNumber load the "x.png" or the "o.png" graphic
    // fetch the x image for player 0, and o image for player 1
    Bit *bit = new Bit();
    bit->LoadTextureFromFile(playerNumber == 0 ? "x.png" : "o.png");
    bit->setOwner(getPlayerAt(playerNumber));
    return bit;
}

//
// setup the game board, this is called once at the start of the game
//
void TicTacToe::setUpBoard()
{
    // create baseline for tic-tac-toe game with 2 players and a 3x3 grid
    setNumberOfPlayers(2);
    _gameOptions.rowX = 3;
    _gameOptions.rowY = 3;

    // here we initialize the images for the board
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            // give some spacing to create a nicer-looking board
            ImVec2 position(x * 100.0f + 50.0f, y * 100.0f + 50.0f);

            // initialization statement
            _grid[y][x].initHolder(position, "square.png", x, y);
        }
    }

    startGame();
}

//
// about the only thing we need to actually fill out for tic-tac-toe
//
bool TicTacToe::actionForEmptyHolder(BitHolder *holder)
{
    // 1) Guard clause: if holder is nullptr, fail fast.
    if (!holder) return false;

    // 2) Is it actually empty?
    if (!holder->empty()) return false;

    // 3) Place the current player's piece on this holder:
    Player *currentPlayer = getCurrentPlayer();
    if (!currentPlayer) return false;

    int playerNumber = currentPlayer->playerNumber();
    Bit *newBit = PieceForPlayer(playerNumber);

    if (!newBit) return false;

    // position the piece at the holder's position
    newBit->moveTo(holder->getPosition());

    // assign the piece to the holder
    holder->setBit(newBit);

    // check for winner or draw after this move
    Player *winner = checkForWinner();
    if (winner) {
        _winner = winner;
    } else if (checkForDraw()) {
        // game is over but no winner
    }

    // 4) Return whether we actually placed a piece. true = acted, false = ignored.
    return true;
}

bool TicTacToe::canBitMoveFrom(Bit *bit, BitHolder *src)
{
    // you can't move anything in tic tac toe
    return false;
}

bool TicTacToe::canBitMoveFromTo(Bit* bit, BitHolder*src, BitHolder*dst)
{
    // you can't move anything in tic tac toe
    return false;
}

//
// free all the memory used by the game on the heap
//
void TicTacToe::stopGame()
{
    // go through the array and call destroyBit on each square
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            _grid[y][x].destroyBit();
        }
    }
}

//
// helper function for the winner check
//
Player* TicTacToe::ownerAt(int index ) const
{
    // convert the index to coordinates, return nullptr if no bit, else return the owner
    int y = index / 3;
    int x = index % 3;

    Bit *bit = _grid[y][x].bit();

    if (!bit) return nullptr;

    return bit->getOwner();
}

Player* TicTacToe::checkForWinner()
{
    // check winning triples given to me before starting the assignment
    int winningCombinations[8][3] = {
        // rows
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        // columns
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        // diagonals
        {0, 4, 8},
        {2, 4, 6}
    };

    // check each winning combination
    for (int i = 0; i < 8; i++) {
        Player *owner1 = ownerAt(winningCombinations[i][0]);
        Player *owner2 = ownerAt(winningCombinations[i][1]);
        Player *owner3 = ownerAt(winningCombinations[i][2]);

        if (owner1 && owner1 == owner2 && owner2 == owner3) {
            return owner1;
        }
    }

    return nullptr;
}

bool TicTacToe::checkForDraw()
{
    // if the board is full and a winner hasn't been found, it's a draw
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (_grid[y][x].empty()) {
                return false;
            }
        }
    }

    return true;
}

//
// state strings
//
std::string TicTacToe::initialStateString()
{
    return "000000000";
}

//
// this still needs to be tied into imguis init and shutdown
// we will read the state string and store it in each turn object
//
std::string TicTacToe::stateString() const
{
    std::string state = "";

    // return a string representing the current state of the board
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            Bit *bit = _grid[y][x].bit();

            if (!bit) {
                state += '0';
            } else {
                int playerNum = bit->getOwner()->playerNumber() + 1;
                state += std::to_string(playerNum);
            }
        }
    }

    return state;
}

//
// this still needs to be tied into imguis init and shutdown
// when the program starts it will load the current game from the imgui ini file and set the game state to the last saved state
//
void TicTacToe::setStateString(const std::string &s)
{
    // set the state of the board from the given string, done by looping through the string and calling setBit on each position on the baord
    int index = 0;

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int playerNumber = s[index] - '0';

            if (playerNumber == 0) {
                _grid[y][x].setBit(nullptr);
            } else if (playerNumber == 1 || playerNumber == 2) {
                Bit *bit = PieceForPlayer(playerNumber - 1);
                bit->moveTo(_grid[y][x].getPosition());
                _grid[y][x].setBit(bit);
            }

            index++;
        }
    }
}


//
// this is the function that will be called by the AI
//
void TicTacToe::updateAI() 
{
    // we will implement the AI in the next assignment!
}

