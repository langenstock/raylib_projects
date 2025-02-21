#ifndef MOVES_H
#define MOVES_H

#include <vector>
#include "square.h"
#include "enums.h"
std::vector<ChessSquare *> GetValidMoves(ChessSquare (&board)[8][8], int start_i, int start_j, EPiece ePiece, ETeam eTeam, bool pieceHasMovedBefore, bool whiteIsInCheck, bool blackIsInCheck);
bool IsKingInCheck(ChessSquare (&board)[8][8], int king_i, int king_j, ETeam eTeam);

std::vector<ChessSquare *> GetValidMoves_Pawn_White(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_Pawn_Black(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_Bishop(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_Knight(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_Rook(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_Queen(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);
std::vector<ChessSquare *> GetValidMoves_King(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore);

std::vector<ChessSquare *> RunLineChecks(int i_dir, int j_dir, ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore, std::vector<ChessSquare *> &moves);

#endif // MOVES_H