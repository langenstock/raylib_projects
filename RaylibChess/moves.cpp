#include "moves.h"
#include <utility>
#include <iostream>
#include <memory>

std::vector<ChessSquare *> GetValidMoves(ChessSquare (&board)[8][8], int start_i, int start_j, EPiece ePiece, ETeam eTeam, bool pieceHasMovedBefore, bool whiteIsInCheck, bool blackIsInCheck)
{
    std::vector<ChessSquare *> moves;

    switch (ePiece)
    {
    case (EPiece::Pawn):
        if (eTeam == ETeam::White)
        {
            moves = GetValidMoves_Pawn_White(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        }
        else
        {
            moves = GetValidMoves_Pawn_Black(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        }
        break;
    case (EPiece::Bishop):
        moves = GetValidMoves_Bishop(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        break;
    case (EPiece::Knight):
        moves = GetValidMoves_Knight(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        break;
    case (EPiece::Rook):
        moves = GetValidMoves_Rook(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        break;
    case (EPiece::Queen):
        moves = GetValidMoves_Queen(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        break;
    case (EPiece::NONE):
        break;
    case (EPiece::King):
        moves = GetValidMoves_King(board, start_i, start_j, eTeam, pieceHasMovedBefore);
        break;
    }
    return moves;
}

bool IsKingInCheck(ChessSquare (&board)[8][8], int king_i, int king_j, ETeam eTeam)
{
    ChessSquare *kingSquare = &board[king_i][king_j];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ChessSquare *sq = &board[i][j];
            ETeam thisSquareTeam = sq->GetTeam();
            if (thisSquareTeam != ETeam::NONE && thisSquareTeam != eTeam)
            {
                EPiece thisSqPiece = sq->GetPiece();
                ETeam team = sq->GetTeam();
                bool hasMoved = sq->HasPieceMovedBefore();

                std::vector<ChessSquare *> moves;

                moves = GetValidMoves(board, sq->GetI(), sq->GetJ(), thisSqPiece, team, hasMoved, false, false);

                for (ChessSquare *s : moves)
                {

                    if (s->GetPiece() == EPiece::King && s->GetI() < 8 && s->GetJ() < 8)
                    {
                        if (s->TrashData())
                        {
                            std::cout << "Trash data!" << std::endl;
                        }
                        else
                        {
                            // std::cout << "piece at i: " << sq->GetI() << ", j: " << sq->GetJ() << " can give check?" << std::endl;

                            kingSquare->SetSquareStatus(ESquareStatus::KingInCheck);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

std::vector<ChessSquare *> GetValidMoves_Pawn_White(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    if (start_j > 0)
    {
        ChessSquare *sq = &board[start_i][start_j - 1];
        EPiece pieceOcc = sq->GetPiece();
        if (pieceOcc == EPiece::NONE)
        {
            moves.push_back(sq);
            if (!pieceHasMovedBefore && (start_j - 2 >= 0))
            {
                sq = &board[start_i][start_j - 2];
                pieceOcc = sq->GetPiece();
                if (pieceOcc == EPiece::NONE)
                {
                    moves.push_back(sq);
                }
            }
        }
    }

    auto checkSquare = [&](int i, int j)
    {
        ChessSquare *sq = &board[i][j];
        EPiece pieceOcc = sq->GetPiece();
        if (pieceOcc != EPiece::NONE)
        {
            if (sq->GetIsOpposingTeam(eTeam))
            {
                moves.push_back(sq);
            }
        }
    };

    checkSquare(start_i - 1, start_j - 1);
    checkSquare(start_i + 1, start_j - 1);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_Pawn_Black(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    if (start_j < 7)
    {
        ChessSquare *sq = &board[start_i][start_j + 1];
        EPiece pieceOcc = sq->GetPiece();
        if (pieceOcc == EPiece::NONE)
        {
            moves.push_back(sq);
            if (!pieceHasMovedBefore && (start_j + 2 < 8))
            {
                sq = &board[start_i][start_j + 2];
                pieceOcc = sq->GetPiece();
                if (pieceOcc == EPiece::NONE)
                {
                    moves.push_back(sq);
                }
            }
        }
    }

    // Evaluate diagonal moves
    auto checkSquare = [&](int i, int j)
    {
        ChessSquare *sq = &board[i][j];
        EPiece pieceOcc = sq->GetPiece();
        if (pieceOcc != EPiece::NONE)
        {
            if (sq->GetIsOpposingTeam(eTeam))
            {
                moves.push_back(sq);
            }
        }
    };

    checkSquare(start_i - 1, start_j + 1);
    checkSquare(start_i + 1, start_j + 1);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_Bishop(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    RunLineChecks(1, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(1, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_Knight(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    auto checkSquare = [&](int i, int j)
    {
        if (i >= 0 && i < 8 && j >= 0 && j < 8)
        {
            ChessSquare *sq = &board[i][j];
            ETeam teamOfOtherPiece = sq->GetTeam();
            if (teamOfOtherPiece != eTeam) // teamOfOtherPiece could be NONE at this point, i.e. no piece
            {
                moves.push_back(sq);
            }
        }
    };

    checkSquare(start_i - 2, start_j - 1);
    checkSquare(start_i - 2, start_j + 1);
    checkSquare(start_i - 1, start_j - 2);
    checkSquare(start_i - 1, start_j + 2);
    checkSquare(start_i + 2, start_j + 1);
    checkSquare(start_i + 2, start_j - 1);
    checkSquare(start_i + 1, start_j - 2);
    checkSquare(start_i + 1, start_j + 2);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_Rook(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    RunLineChecks(1, 0, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, 0, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(0, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(0, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_Queen(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    RunLineChecks(1, 0, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, 0, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(0, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(0, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(1, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(1, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, -1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);
    RunLineChecks(-1, 1, board, start_i, start_j, eTeam, pieceHasMovedBefore, moves);

    return moves;
}

std::vector<ChessSquare *> GetValidMoves_King(ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore)
{
    std::vector<ChessSquare *> moves;

    auto checkSquare = [&](int i, int j)
    {
        if (i >= 0 && i < 8 && j >= 0 && j < 8)
        {
            ChessSquare *sq = &board[i][j];
            ETeam teamOfOtherPiece = sq->GetTeam();
            if (teamOfOtherPiece != eTeam) // teamOfOtherPiece could be NONE at this point, i.e. no piece
            {
                moves.push_back(sq);
            }
        }
    };

    checkSquare(start_i - 1, start_j - 1);
    checkSquare(start_i - 1, start_j);
    checkSquare(start_i - 1, start_j + 1);
    checkSquare(start_i, start_j - 1);
    checkSquare(start_i, start_j + 1);
    checkSquare(start_i + 1, start_j - 1);
    checkSquare(start_i + 1, start_j);
    checkSquare(start_i + 1, start_j + 1);

    // Special case Castling
    if (!pieceHasMovedBefore)
    {
        // Rook pieces are 3 spaces right or 4 spaces left for both black and white
        if (board[start_i + 1][start_j].GetIsEmpty() && board[start_i + 2][start_j].GetIsEmpty())
        {
            ChessSquare *sq = &board[start_i + 3][start_j];

            if (sq->GetPiece() == EPiece::Rook)
            {
                if (sq->GetIsSameTeam(eTeam))
                {
                    ChessSquare *castlingSquare = &board[start_i + 2][start_j];
                    castlingSquare->SetMoveToHereIsCastling(true);
                    moves.push_back(castlingSquare);
                }
            }
        }

        // Potential Castling to the left
        if (board[start_i - 1][start_j].GetIsEmpty() && board[start_i - 2][start_j].GetIsEmpty() && board[start_i - 3][start_j].GetIsEmpty())
        {
            ChessSquare *sq = &board[start_i - 4][start_j];

            if (sq->GetPiece() == EPiece::Rook)
            {
                if (sq->GetIsSameTeam(eTeam))
                {
                    ChessSquare *castlingSquare = &board[start_i - 3][start_j];
                    castlingSquare->SetMoveToHereIsCastling(true);
                    moves.push_back(castlingSquare);
                }
            }
        }
    }

    return moves;
}

std::vector<ChessSquare *> RunLineChecks(int i_dir, int j_dir, ChessSquare (&board)[8][8], int start_i, int start_j, ETeam eTeam, bool pieceHasMovedBefore, std::vector<ChessSquare *> &moves)
{
    for (int incr = 1; incr < 8; incr++)
    {
        int i = start_i + incr * i_dir;
        int j = start_j + incr * j_dir;

        if (i == 3 && j == 0)
        {
            int a = 1;
        }

        if (i < 0 || i > 7 || j < 0 || j > 7)
        {
            break;
        }

        ChessSquare *sq = &board[i][j];
        EPiece ePc = sq->GetPiece();
        if (ePc == EPiece::NONE)
        {
            moves.push_back(sq);
        }
        else if (ePc != EPiece::NONE)
        {
            if (sq->GetTeam() != eTeam) // i.e. if the piece on this square is the other team
            {
                moves.push_back(sq);
                break;
            }

            break; // This square is occupied by ally piece
        }
    }

    return moves;
}