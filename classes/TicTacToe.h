#pragma once
#include "Game.h"
#include "Square.h"

//
// the classic game of tic tac toe
//

//
// the main game class
//
class TicTacToe : public Game
{
public:
    TicTacToe();
    ~TicTacToe();

    // set up the board
    void        setUpBoard() override;

    Player*     checkForWinner() override;
    bool        checkForDraw() override;
    std::string initialStateString() override;
    std::string stateString() const override;
    void        setStateString(const std::string &s) override;
    bool        actionForEmptyHolder(BitHolder *holder) override;
    bool        canBitMoveFrom(Bit*bit, BitHolder *src) override;
    bool        canBitMoveFromTo(Bit* bit, BitHolder*src, BitHolder*dst) override;
    void        stopGame() override;

	void        updateAI() override;
    bool        gameHasAI() override { return true; }
    BitHolder &getHolderAt(const int x, const int y) override { return _grid[y][x]; }
private:
    Bit *       PieceForPlayer(const int playerNumber);
    Player*     ownerAt(int index ) const;

    // added helper functions for the AI
    int         negamax(int depth, int currentPlayer, int maxDepth, int board[9]);
    int         evaluateBoard(int board[9]);
    int         checkWinnerInBoard(int board[9]);
    bool        isBoardFullArray(int board[9]) const;
    int         findBestMove();
    int         countEmptySquares() const;

    Square      _grid[3][3];
};

