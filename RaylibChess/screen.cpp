#include "screen.h"
#include <iostream>
#include <optional>

Screen::Screen()
{
}

Screen::Screen(bool debugBoard)
{
    if (debugBoard)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                board[i][j] = ChessSquare(i, j, ETeam::NONE, EPiece::NONE, false);
            }
        }

        bool hasMoved = false;

        board[3][0].SetPiece(EPiece::Queen, ETeam::Black, hasMoved);
        board[3][7].SetPiece(EPiece::Queen, ETeam::White, hasMoved);
        board[6][2].SetPiece(EPiece::Knight, ETeam::White, hasMoved);
        board[5][1].SetPiece(EPiece::Knight, ETeam::Black, hasMoved);
        board[1][1].SetPiece(EPiece::Pawn, ETeam::Black, hasMoved);
        board[1][3].SetPiece(EPiece::Pawn, ETeam::White, hasMoved);
    }
    else
    {
        // Black team
        board[0][0] = ChessSquare(0, 0, ETeam::Black, EPiece::Rook, false);
        board[1][0] = ChessSquare(1, 0, ETeam::Black, EPiece::Knight, false);
        board[2][0] = ChessSquare(2, 0, ETeam::Black, EPiece::Bishop, false);
        board[3][0] = ChessSquare(3, 0, ETeam::Black, EPiece::Queen, false);
        board[4][0] = ChessSquare(4, 0, ETeam::Black, EPiece::King, false);
        board[5][0] = ChessSquare(5, 0, ETeam::Black, EPiece::Bishop, false);
        board[6][0] = ChessSquare(6, 0, ETeam::Black, EPiece::Knight, false);
        board[7][0] = ChessSquare(7, 0, ETeam::Black, EPiece::Rook, false);
        // Pawn Row Black Team
        board[0][1] = ChessSquare(0, 1, ETeam::Black, EPiece::Pawn, false);
        board[1][1] = ChessSquare(1, 1, ETeam::Black, EPiece::Pawn, false);
        board[2][1] = ChessSquare(2, 1, ETeam::Black, EPiece::Pawn, false);
        board[3][1] = ChessSquare(3, 1, ETeam::Black, EPiece::Pawn, false);
        board[4][1] = ChessSquare(4, 1, ETeam::Black, EPiece::Pawn, false);
        board[5][1] = ChessSquare(5, 1, ETeam::Black, EPiece::Pawn, false);
        board[6][1] = ChessSquare(6, 1, ETeam::Black, EPiece::Pawn, false);
        board[7][1] = ChessSquare(7, 1, ETeam::Black, EPiece::Pawn, false);

        // Blank squares
        for (int j = 2; j < 6; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                board[i][j] = ChessSquare(i, j, ETeam::NONE, EPiece::NONE, false);
            }
        }

        // Pawn row White team
        board[0][6] = ChessSquare(0, 6, ETeam::White, EPiece::Pawn, false);
        board[1][6] = ChessSquare(1, 6, ETeam::White, EPiece::Pawn, false);
        board[2][6] = ChessSquare(2, 6, ETeam::White, EPiece::Pawn, false);
        board[3][6] = ChessSquare(3, 6, ETeam::White, EPiece::Pawn, false);
        board[4][6] = ChessSquare(4, 6, ETeam::White, EPiece::Pawn, false);
        board[5][6] = ChessSquare(5, 6, ETeam::White, EPiece::Pawn, false);
        board[6][6] = ChessSquare(6, 6, ETeam::White, EPiece::Pawn, false);
        board[7][6] = ChessSquare(7, 6, ETeam::White, EPiece::Pawn, false);

        board[0][7] = ChessSquare(0, 7, ETeam::White, EPiece::Rook, false);
        board[1][7] = ChessSquare(1, 7, ETeam::White, EPiece::Knight, false);
        board[2][7] = ChessSquare(2, 7, ETeam::White, EPiece::Bishop, false);
        board[3][7] = ChessSquare(3, 7, ETeam::White, EPiece::Queen, false);
        board[4][7] = ChessSquare(4, 7, ETeam::White, EPiece::King, false);
        board[5][7] = ChessSquare(5, 7, ETeam::White, EPiece::Bishop, false);
        board[6][7] = ChessSquare(6, 7, ETeam::White, EPiece::Knight, false);
        board[7][7] = ChessSquare(7, 7, ETeam::White, EPiece::Rook, false);
    }

    sprites = Sprites();
    currentlySelectedSquare = nullptr;
    whiteTurn = true;
}

void Screen::DrawGameBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ChessSquare *sq = &board[i][j];
            sq->DrawSquare(&sprites);
        }
    }

    if (eScreenMode == EScreenMode::PawnTransformPopupMenu_White)
    {
        DrawText("Press Q", 500, 100, 30, WHITE);
    }
}

void Screen::DeselectSquare(ChessSquare *squareWeClickedOn)
{
    squareWeClickedOn->SetSquareStatus(ESquareStatus::Idle);
    currentlySelectedSquare = nullptr;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].SetSquareStatus(ESquareStatus::Idle);
        }
    }
}

bool Screen::AttemptMove(ChessSquare *sqWeClickedOn, bool simulate)
{
    // Check if a valid move
    if (sqWeClickedOn->GetIsValidMove())
    {
        // We can move here!

        // First clone a copy of the square, before the move, in case we need to undo it
        ChessSquare squareAfterMove = ChessSquare(sqWeClickedOn->GetI(), sqWeClickedOn->GetJ(), sqWeClickedOn->GetTeam(), sqWeClickedOn->GetPiece(), sqWeClickedOn->HasPieceMovedBefore());
        ChessSquare squareBeforeMove = ChessSquare(currentlySelectedSquare->GetI(), currentlySelectedSquare->GetJ(), currentlySelectedSquare->GetTeam(), currentlySelectedSquare->GetPiece(), currentlySelectedSquare->HasPieceMovedBefore());

        // Set data on sq to the stuff that was in currentlySelectedSquare
        sqWeClickedOn->SetPiece(currentlySelectedSquare->GetPiece(), currentlySelectedSquare->GetTeam(), true);

        // Evaluate Pawn reaching last row
        if (sqWeClickedOn->GetPiece() == EPiece::Pawn)
        {
            if (sqWeClickedOn->GetJ() == 0 && sqWeClickedOn->GetTeam() == ETeam::White)
            {
                sqWeClickedOn->SetPiece(EPiece::Queen, sqWeClickedOn->GetTeam(), false);
            }
            else if (sqWeClickedOn->GetJ() == 7 && sqWeClickedOn->GetTeam() == ETeam::Black)
            {
                sqWeClickedOn->SetPiece(EPiece::Queen, sqWeClickedOn->GetTeam(), false);
            }
        }

        ChessSquare rookBeforeCastling;
        ChessSquare rookAfterCastling;
        bool rookCastlingExists = false;

        // Special case for Castling King and Rook
        if (sqWeClickedOn->GetMoveToHereIsCastling())
        {
            if (sqWeClickedOn->GetI() == 6)
            {
                // Rook moves from 7 to 5
                ChessSquare *expectedRookSq = &board[7][sqWeClickedOn->GetJ()];
                if (expectedRookSq->GetPiece() == EPiece::Rook)
                {
                    if (expectedRookSq->GetTeam() == currentlySelectedSquare->GetTeam())
                    {
                        // The square the rook will move to for castling
                        ChessSquare *rookDest = &board[5][sqWeClickedOn->GetJ()];

                        // Store the 'before' rook square incase we need to undo this move
                        rookBeforeCastling = ChessSquare(expectedRookSq->GetI(), expectedRookSq->GetJ(), expectedRookSq->GetTeam(), expectedRookSq->GetPiece(), expectedRookSq->HasPieceMovedBefore());
                        rookAfterCastling = ChessSquare(rookDest->GetI(), rookDest->GetJ(), rookDest->GetTeam(), rookDest->GetPiece(), rookDest->HasPieceMovedBefore());
                        rookCastlingExists = true;

                        rookDest->SetPiece(EPiece::Rook, currentlySelectedSquare->GetTeam(), true);
                        expectedRookSq->SetSquareAsEmpty();
                    }
                }
            }
            else if (sqWeClickedOn->GetI() == 1)
            {
                // Rook moves from 0 to 2
                ChessSquare *expectedRookSq = &board[0][sqWeClickedOn->GetJ()];
                if (expectedRookSq->GetPiece() == EPiece::Rook)
                {
                    if (expectedRookSq->GetTeam() == currentlySelectedSquare->GetTeam())
                    {
                        // Store the 'before' rook square incase we need to undo this move
                        rookBeforeCastling = ChessSquare(expectedRookSq->GetI(), expectedRookSq->GetJ(), expectedRookSq->GetTeam(), expectedRookSq->GetPiece(), expectedRookSq->HasPieceMovedBefore());
                        rookCastlingExists = true;

                        board[2][sqWeClickedOn->GetJ()].SetPiece(EPiece::Rook, currentlySelectedSquare->GetTeam(), true);
                        expectedRookSq->SetSquareAsEmpty();
                    }
                }
            }
        }
        // Set data on currently selected square to none, etc.
        currentlySelectedSquare->SetSquareAsEmpty();

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                ChessSquare *sqToReset = &board[i][j];

                sqToReset->SetSquareIsKingInCheck(false);
                sqToReset->SetSquareStatus(ESquareStatus::Idle);

                sqToReset->SetMoveToHereIsCastling(false);

                if (sqToReset->GetPiece() == EPiece::King)
                {
                    if (sqToReset->GetTeam() == ETeam::Black)
                    {
                        blackKingLocation = sqToReset;
                    }
                    else
                    {
                        whiteKingLocation = sqToReset;
                    }
                }
            }
        }

        whiteKingInCheck = IsKingInCheck(board, whiteKingLocation->GetI(), whiteKingLocation->GetJ(), ETeam::White);
        blackKingInCheck = IsKingInCheck(board, blackKingLocation->GetI(), blackKingLocation->GetJ(), ETeam::Black);

        // Here we evaluate whether we should undo the move
        // If this move leaves the king in check or if he WAS in check
        // and still is in check, we undo the move

        bool undoMoveBecauseOfCheck = false;
        if ((whiteTurn && whiteKingInCheck) || (!whiteTurn && blackKingInCheck))
        {
            // meaning white was already in check and now still is or similary for black
            // UNDO move
            undoMoveBecauseOfCheck = true;

            // Restore the 'before' Square
            int before_i = squareBeforeMove.GetI();
            int before_j = squareBeforeMove.GetJ();
            board[before_i][before_j].SetPiece(squareBeforeMove.GetPiece(), squareBeforeMove.GetTeam(), squareBeforeMove.HasPieceMovedBefore());
            int after_i = squareAfterMove.GetI();
            int after_j = squareAfterMove.GetJ();
            board[after_i][after_j].SetPiece(squareAfterMove.GetPiece(), squareAfterMove.GetTeam(), squareAfterMove.HasPieceMovedBefore());

            // If this move was a castling, we need to undo the Rook move as well
            if (rookCastlingExists)
            {
                int b_i = rookBeforeCastling.GetI();
                int b_j = rookBeforeCastling.GetJ();
                board[b_i][b_j].SetPiece(rookBeforeCastling.GetPiece(), rookBeforeCastling.GetTeam(), rookBeforeCastling.HasPieceMovedBefore());

                int a_i = rookAfterCastling.GetI();
                int a_j = rookAfterCastling.GetJ();
                board[a_i][a_j].SetPiece(rookAfterCastling.GetPiece(), rookAfterCastling.GetTeam(), rookAfterCastling.HasPieceMovedBefore());
            }

            // Evaluate check again, now that we've undone the move
            whiteKingInCheck = IsKingInCheck(board, whiteKingLocation->GetI(), whiteKingLocation->GetJ(), ETeam::White);
            blackKingInCheck = IsKingInCheck(board, blackKingLocation->GetI(), blackKingLocation->GetJ(), ETeam::Black);
        }

        whiteKingLocation->SetSquareIsKingInCheck(whiteKingInCheck);
        blackKingLocation->SetSquareIsKingInCheck(blackKingInCheck);

        if (!undoMoveBecauseOfCheck)
        {
            whiteTurn = !whiteTurn;
        }
        currentlySelectedSquare = nullptr;

        // TODO DL we do this twice ... not the best
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                board[i][j].SetSquareStatus(ESquareStatus::Idle);
            }
        }
        return (!undoMoveBecauseOfCheck); // return false if the move had to be cancelled due to being in check
    }
    return false;
}

void Screen::EvaluateClickedSquare(int mouseX, int mouseY)
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ChessSquare *sqWeClickedOn = &board[i][j];

            if (sqWeClickedOn->IsSquareClickedOn(mouseX, mouseY))
            {
                ETeam teamOccupying = sqWeClickedOn->GetTeam();

                if (currentlySelectedSquare) // meaning there is a currently selected square, not necessarily this one
                {
                    if (currentlySelectedSquare == sqWeClickedOn)
                    {
                        DeselectSquare(sqWeClickedOn);
                        break;
                    }
                    else if (teamOccupying == currentlySelectedSquare->GetTeam())
                    {
                        DeselectSquare(currentlySelectedSquare);
                        break;
                    }
                    else // We are attempting a move. Need to check if valid
                    {
                        bool simulation = false;
                        AttemptMove(sqWeClickedOn, simulation);

                        bool wasWhiteTurnBeforeCheckSim = whiteTurn;

                        // Evaluate Checkmate here
                        if (whiteKingInCheck)
                        {
                            // Simulate White King Moves in all direction
                            int i = whiteKingLocation->GetI();
                            int j = whiteKingLocation->GetJ();

                            std::vector<ChessSquare *> moves = GetValidMoves(board, i, j, EPiece::King, ETeam::White, whiteKingLocation->HasPieceMovedBefore(), whiteKingInCheck, blackKingInCheck);

                            simulation = true;
                            bool possibleMoveFound = false;
                            for (size_t i = 0; i < moves.size(); i++)
                            {
                                whiteTurn = true; // we use this to force simulation behaviour
                                currentlySelectedSquare = whiteKingLocation;
                                bool movedIntoCheck = AttemptMove(moves[i], simulation);
                                if (!movedIntoCheck)
                                {
                                    possibleMoveFound = true;
                                }
                            }

                            if (possibleMoveFound)
                            {
                                // Not checkmate
                            }
                            else
                            {
                                // IS'a CHECK'a'MATE
                            }
                            currentlySelectedSquare = nullptr;
                            whiteTurn = wasWhiteTurnBeforeCheckSim;
                        }

                        break;
                        // Else not a valid move and so do nothing
                    }
                }
                else // There are no currently selected squares, can click any of our pieces
                {
                    // Can only select one of our pieces at this point
                    if ((whiteTurn && teamOccupying == ETeam::White) || (!whiteTurn && teamOccupying == ETeam::Black))
                    {
                        ESquareStatus currentStatus = sqWeClickedOn->GetSquareStatus();

                        if (currentStatus == ESquareStatus::Idle || currentStatus == ESquareStatus::KingInCheck)
                        {
                            sqWeClickedOn->SetSquareStatus(ESquareStatus::Selected);
                            currentlySelectedSquare = sqWeClickedOn;

                            // Set all valid moves to green as well here
                            std::vector<ChessSquare *> moves = GetValidMoves(board, sqWeClickedOn->GetI(), sqWeClickedOn->GetJ(), sqWeClickedOn->GetPiece(), sqWeClickedOn->GetTeam(), sqWeClickedOn->HasPieceMovedBefore(), whiteKingInCheck, blackKingInCheck);

                            // then go through that list and make sure they're all valid, not blocked by pieces, not check etc.
                            unsigned long long s = moves.size();
                            for (unsigned long long i = 0; i < s; i++)
                            {
                                moves[i]->SetSquareStatus(ESquareStatus::ValidMove);
                            }

                            // Not having the loop below resulted in a dealloc error for some reason
                            for (ChessSquare *cSq : moves)
                            {
                                cSq = nullptr;
                            }
                        }
                    }
                }
                return;
            }
        }
    }
}

void Screen::SetScreenMode(EScreenMode mode)
{
    eScreenMode = mode;
}

EScreenMode Screen::GetScreenMode()
{
    return eScreenMode;
}

void Screen::UnloadAllSprites()
{
    sprites.UnloadAll();
}

void Screen::CheckMate(ETeam team)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            ChessSquare *sq = &board[i][j];
            ETeam thisSqTeam = sq->GetTeam();
            if (thisSqTeam == team)
            {
                sq->SetSquareStatus(ESquareStatus::Won);
            }
            else if (thisSqTeam != ETeam::NONE)
            {
                sq->SetSquareStatus(ESquareStatus::Lost);
            }
        }
    }

    eScreenMode = EScreenMode::Checkmate;
}
