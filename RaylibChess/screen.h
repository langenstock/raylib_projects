#pragma once
#include <raylib.h>
#include <vector>
#include "enums.h"
#include "square.h"
#include "sprites.h"
#include "moves.h"
#include <utility>

class Screen
{
public:
    Screen();
    Screen(bool debugBoard);
    void DrawGameBoard();
    void EvaluateClickedSquare(int mouseX, int mouseY);
    void SetScreenMode(EScreenMode mode);
    EScreenMode GetScreenMode();
    void UnloadAllSprites();
    void CheckMate(ETeam team);

    bool whiteTurn;

    bool whiteKingInCheck = false;
    bool blackKingInCheck = false;

private:
    void DeselectSquare(ChessSquare *squareWeClickedOn);
    bool AttemptMove(ChessSquare *sqWeClickedOn, bool simulate);

    ChessSquare board[8][8]; // board is of the format board[row][col]
    Sprites sprites;
    bool squareCurrentlySelected;
    ChessSquare *currentlySelectedSquare;
    std::vector<ChessSquare *> nonIdleSquares;
    ChessSquare *whiteKingLocation;
    ChessSquare *blackKingLocation;

    EScreenMode eScreenMode = EScreenMode::Play;
};