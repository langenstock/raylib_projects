#include "square.h"
#include <iostream>

ChessSquare::ChessSquare()
{
}

ChessSquare::ChessSquare(int i, int j, ETeam eTeam, EPiece ePiece, bool pieceHasMovedBefore)
{
    // Square colour
    // (0, 0) is white
    if (i % 2 == 0)
    {
        eSquareColour = (j % 2 == 0) ? ESquareColour::White : ESquareColour::Black;
    }
    else if (i % 2 == 1)
    {
        eSquareColour = (j % 2 == 1) ? ESquareColour::White : ESquareColour::Black;
    }

    colour = (eSquareColour == ESquareColour::White) ? LIGHTGRAY : DARKBROWN;
    idleColour = colour;

    this->i = i;
    this->j = j;

    x = BOARD_START_X + (i * width);
    y = BOARD_START_Y + (j * width);

    xMin = x;
    xMax = x + width;
    yMin = y;
    yMax = y + width;

    ePieceOccupying = ePiece;
    this->eTeam = eTeam;

    eSquareStatus = ESquareStatus::Idle;
    this->pieceHasMovedBefore = pieceHasMovedBefore;
}

void ChessSquare::DrawSquare(Sprites *sprites)
{
    DrawRectangle(x, y, width, width, colour);

    if (ePieceOccupying != EPiece::NONE)
    {
        if (eTeam != ETeam::NONE)
        {
            Texture2D *texture = sprites->GetTexture(eTeam, ePieceOccupying);
            if (texture)
            {
                DrawTextureEx(*texture, {static_cast<float>(x), static_cast<float>(y)}, 0, 0.3, WHITE);
            }
        }
    }
}

bool ChessSquare::IsSquareClickedOn(int mouseX, int mouseY)
{
    if (mouseX > xMin && mouseX < xMax && mouseY > yMin && mouseY < yMax)
    {
        // std::cout << "clicked on {" << i << ", " << j << "}" << std::endl;

        return true;
    }

    return false;
}

void ChessSquare::SetSquareStatus(ESquareStatus status)
{
    eSquareStatus = status;

    switch (eSquareStatus)
    {
    case (ESquareStatus::Idle):
        if (kingIsInCheck)
        {
            colour = RED;
            eSquareStatus = ESquareStatus::KingInCheck;
        }
        else
        {
            colour = idleColour;
        }
        break;
    case (ESquareStatus::Selected):
        if (kingIsInCheck)
        {
            eSquareStatus = ESquareStatus::SelectedAndKingInCheck;
            colour = DARKBLUE;
        }
        else
        {
            colour = (eSquareColour == ESquareColour::White) ? GREEN : DARKGREEN;
        }
        break;
    case (ESquareStatus::ValidMove):
        colour = (eSquareColour == ESquareColour::White) ? GREEN : DARKGREEN;
        break;
    case (ESquareStatus::InvalidMove):
        colour = idleColour;
        break;
    case (ESquareStatus::KingInCheck):
        colour = RED;
        kingIsInCheck = true;
        break;
    case (ESquareStatus::Won):
        colour = (eSquareColour == ESquareColour::Black) ? DARKGREEN : GREEN;
        break;
    case (ESquareStatus::Lost):
        colour = (eSquareColour == ESquareColour::Black) ? RED : PINK;
        break;
    }
    if (kingIsInCheck)
    {
    }
}

ESquareStatus ChessSquare::GetSquareStatus()
{
    return eSquareStatus;
}

bool ChessSquare::GetIsValidMove()
{
    return (eSquareStatus == ESquareStatus::ValidMove) ? true : false;
}

int ChessSquare::GetI()
{
    return i;
}

int ChessSquare::GetJ()
{
    return j;
}

ETeam ChessSquare::GetTeam()
{
    return eTeam;
}

bool ChessSquare::GetIsOpposingTeam(ETeam teamToCheckAgainst)
{
    if (eTeam != ETeam::NONE)
    {
        if (eTeam != teamToCheckAgainst)
        {
            return true;
        }
    }
    return false;
}

bool ChessSquare::GetIsSameTeam(ETeam teamInQuestion)
{
    if (eTeam != ETeam::NONE)
    {
        if (eTeam == teamInQuestion)
        {
            return true;
        }
    }
    return false;
}

EPiece ChessSquare::GetPiece()
{
    return ePieceOccupying;
}

bool ChessSquare::GetIsEmpty()
{
    return (ePieceOccupying == EPiece::NONE) ? true : false;
}

void ChessSquare::SetPiece(EPiece ePiece, ETeam team, bool setHasMovedBefore)
{
    ePieceOccupying = ePiece;
    eTeam = team;
    pieceHasMovedBefore = setHasMovedBefore;
}

void ChessSquare::SetSquareAsEmpty()
{
    ePieceOccupying = EPiece::NONE;
    eTeam = ETeam::NONE;
    pieceHasMovedBefore = false;
}

bool ChessSquare::HasPieceMovedBefore()
{
    return pieceHasMovedBefore;
}

bool ChessSquare::GetMoveToHereIsCastling()
{
    return moveToHereIsACastling;
}

void ChessSquare::SetMoveToHereIsCastling(bool is)
{
    moveToHereIsACastling = is;
}
bool ChessSquare::GetSquareIsKingInCheck()
{
    return kingIsInCheck;
}
void ChessSquare::SetSquareIsKingInCheck(bool check)
{
    kingIsInCheck = check;
    if (kingIsInCheck)
    {
        SetSquareStatus(ESquareStatus::KingInCheck);
    }
    else
    {
        SetSquareStatus(ESquareStatus::Idle);
    }
}

bool ChessSquare::TrashData()
{
    if (x == 0 || y == 0 || width == 0)
    {
        return true;
    }
    return false;
}
