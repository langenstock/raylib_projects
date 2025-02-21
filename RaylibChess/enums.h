#ifndef ENUMS_H
#define ENUMS_H

enum class EScreenMode
{
    Play,
    Pause,
    Menu,
    PawnTransformPopupMenu_White,
    PawnTransformPopupMenu_Black,
    Checkmate,
};

enum EPiece
{
    King,
    Queen,
    Rook,
    Knight,
    Bishop,
    Pawn,
    NONE
};

enum class ETeam
{
    White,
    Black,
    NONE
};

enum class ESquareColour
{
    White,
    Black,
    WhitePreviewMove,
    BlackPreviewMove
};

enum class ESquareStatus
{
    Idle,
    Selected,
    ValidMove,
    InvalidMove,
    KingInCheck,
    SelectedAndKingInCheck,
    Won,
    Lost,
};

#endif // ENUMS_H