#pragma once
#include <raylib.h>
#include "enums.h"
#include "conf.h"
#include "sprites.h"

class ChessSquare
{
public:
    ChessSquare();
    ChessSquare(int i, int j, ETeam eTeam, EPiece ePiece, bool pieceHasMovedBefore);
    void DrawSquare(Sprites *sprites);
    bool IsSquareClickedOn(int mouseX, int mouseY);
    void SetSquareStatus(ESquareStatus status);
    ESquareStatus GetSquareStatus();
    bool GetIsValidMove();
    int GetI();
    int GetJ();
    ETeam GetTeam();
    bool GetIsOpposingTeam(ETeam teamToCheckAgainst);
    bool GetIsSameTeam(ETeam teamInQuestion);
    EPiece GetPiece();
    bool GetIsEmpty();
    void SetPiece(EPiece ePiece, ETeam team, bool setHasMovedBefore);
    void SetSquareAsEmpty();
    bool HasPieceMovedBefore();
    bool GetMoveToHereIsCastling();
    void SetMoveToHereIsCastling(bool is);

    bool GetSquareIsKingInCheck();
    void SetSquareIsKingInCheck(bool check);

    bool TrashData();

private:
    int i; // Grid co ordinate
    int j;
    int x; // Pixel co ordinate
    int y;
    int width = 50;
    ESquareColour eSquareColour;
    Color idleColour;
    Color colour;

    EPiece ePieceOccupying;
    ETeam eTeam;

    ESquareStatus eSquareStatus;

    int xMin;
    int xMax;
    int yMin;
    int yMax;

    bool pieceHasMovedBefore;
    bool moveToHereIsACastling = false;
    bool kingIsInCheck = false;
};