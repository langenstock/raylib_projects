#include "sprites.h"

Sprites::Sprites()
{
    whiteTexMap[Rook] = LoadTexture("sprites/WhiteRook.png");
    whiteTexMap[Knight] = LoadTexture("sprites/WhiteKnight.png");
    whiteTexMap[Bishop] = LoadTexture("sprites/WhiteBishop.png");
    whiteTexMap[Queen] = LoadTexture("sprites/WhiteQueen.png");
    whiteTexMap[King] = LoadTexture("sprites/WhiteKing.png");
    whiteTexMap[Pawn] = LoadTexture("sprites/WhitePawn.png");

    blackTexMap[Rook] = LoadTexture("sprites/BlackRook.png");
    blackTexMap[Knight] = LoadTexture("sprites/BlackKnight.png");
    blackTexMap[Bishop] = LoadTexture("sprites/BlackBishop.png");
    blackTexMap[Queen] = LoadTexture("sprites/BlackQueen.png");
    blackTexMap[King] = LoadTexture("sprites/BlackKing.png");
    blackTexMap[Pawn] = LoadTexture("sprites/BlackPawn.png");
}

Texture2D *Sprites::GetTexture(ETeam eTeam, EPiece ePiece)
{
    if (ePiece == EPiece::NONE || eTeam == ETeam::NONE)
    {
        return nullptr;
    }
    else if (eTeam == ETeam::White)
    {
        return (whiteTexMap.count(ePiece) > 0) ? &whiteTexMap[ePiece] : nullptr;
        // return &whiteTexMap[ePiece];
    }
    else if (eTeam == ETeam::Black)
    {
        if (blackTexMap.count(ePiece) > 0)
        {
            return &blackTexMap[ePiece];
        }
        else
        {
            return nullptr;
        }
    }
}

void Sprites::UnloadAll()
{
    for (const auto &pair : whiteTexMap)
    {
        UnloadTexture(pair.second);
    }

    for (const auto &pair : blackTexMap)
    {
        UnloadTexture(pair.second);
    }
}
