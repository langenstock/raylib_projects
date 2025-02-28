#include "grid.h"
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

Grid::Grid(bool background)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!background)
            {
                ETileState state = ETileState::Empty;
                int v = 0;
                if (i == 3 && j == 3)
                {
                    v = 2;
                    state = ETileState::Stationary;
                }
                if (i == 2 && j == 2)
                {
                    v = 2;
                    state = ETileState::Stationary;
                };
                Tile tile = Tile(i, j, v, state);
                tiles[i][j] = tile;
            }
            else
            // Make a blank copy of the whole grid so that it can be drawn in the background at all times
            {
                Tile tile = Tile(i, j);
                backgroundTiles[i][j] = tile;
            }
        }
    }
}

Tile Grid::getTile(int i, int j)
{
    return tiles[i][j];
}

void Grid::DrawGrid()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile *tile = &tiles[i][j];

            int intValue = tile->GetIntValue();
            std::string str = std::to_string(intValue);
            const char *c_str = str.c_str();
            c_str = (std::strcmp(c_str, "0") == 0) ? "" : c_str;

            Color tileCol = tile->getTileColour();
            Color textCol = tile->getTileTextColour();

            DrawRectangle(tile->GetX() + 1, tile->GetY() + 1, TILE_SIZE - 1, TILE_SIZE - 1, tileCol);

            float fontSize = tile->getTextSize();
            int textWidth = MeasureText(c_str, fontSize);
            float text_xPos = static_cast<float>(tile->GetX()) + TILE_SIZE / 2 - textWidth / 2;

            DrawTextEx(font, c_str, {text_xPos, tile->GetTextPosY()}, fontSize, 5, textCol);
        }
    }
}

void Grid::DrawBackgroundGrid()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile *tile = &backgroundTiles[i][j];
            DrawRectangle(tile->GetX() + 1, tile->GetY() + 1, TILE_SIZE - 1, TILE_SIZE - 1, tileColourMap[2]);
        }
    }
}

void Grid::RunMovementChecks(Tile *t, int i, int j, EMovement dir)
{
    int coordinateToMoveTo_i = i;
    int coordinateToMoveTo_j = j;

    // check 1 above then 2 above etc.
    for (int k = 1; k < 4; k++)
    {
        int incr_i;
        int incr_j;

        switch (dir)
        {
        case (EMovement::Up):
            incr_i = i;
            incr_j = j - k;
            break;
        case (EMovement::Down):
            incr_i = i;
            incr_j = j + k;
            break;
        case (EMovement::Right):
            incr_i = i + k;
            incr_j = j;
            break;
        case (EMovement::Left):
            incr_i = i - k;
            incr_j = j;
            break;
        }

        if (incr_i >= 0 && incr_i < 4 && incr_j >= 0 && incr_j < 4)
        {
            Tile *tileToCheck = &tiles[incr_i][incr_j];
            bool canMerge = tilesCanMerge(t, tileToCheck);
            bool tileAboveIsEmpty = (tileToCheck->GetTileState() == ETileState::Empty);
            if (tileAboveIsEmpty || canMerge)
            {
                coordinateToMoveTo_j = incr_j;
                coordinateToMoveTo_i = incr_i;
            }
        }
    }

    ETileState state = evaluateMoveTilesStateBehaviour(t, &tiles[coordinateToMoveTo_i][coordinateToMoveTo_j]);
    if (state == ETileState::MovingToMerge)
    {
        t->DoubleValue();
    }
    t->SetTileDestination(coordinateToMoveTo_i, coordinateToMoveTo_j, state);

    SetTileOnTilesGrid(coordinateToMoveTo_i, coordinateToMoveTo_j, t);
}

void Grid::ProcessMovement(EMovement dir)
{
    if (eGridState == EGridState::Stationary)
    {
        switch (dir)
        {
        case (EMovement::Up):

            // Get all non-empty tiles. Starting from top row and moving down
            // Top row is j = 0

            for (int j = 1; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    Tile *thisTile = &tiles[i][j];

                    if (thisTile->GetTileState() == ETileState::Stationary)
                    {
                        RunMovementChecks(thisTile, i, j, dir);
                    }
                }
            }

            break;
        case (EMovement::Down):
            // Get all non-empty tiles. Starting from bottom row

            for (int j = 3; j > -1; j--) // bottom to top
            {
                for (int i = 0; i < 4; i++) // left to right
                {
                    Tile *thisTile = &tiles[i][j];

                    if (thisTile->GetTileState() == ETileState::Stationary)
                    {
                        RunMovementChecks(thisTile, i, j, dir);
                    }
                }
            }

            break;
        case (EMovement::Left):

            // look column by column starting from left

            for (int i = 1; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    Tile *thisTile = &tiles[i][j];

                    if (thisTile->GetTileState() == ETileState::Stationary)
                    {
                        RunMovementChecks(thisTile, i, j, dir);
                    }
                }
            }

            break;
        case (EMovement::Right):
            // look column by column starting from right

            for (int i = 3; i >= 0; i--)
            {
                for (int j = 0; j < 4; j++)
                {
                    Tile *thisTile = &tiles[i][j];

                    if (thisTile->GetTileState() == ETileState::Stationary)
                    {
                        RunMovementChecks(thisTile, i, j, dir);
                    }
                }
            }
            break;
        }
    }
}

void Grid::SpawnNewTile()
{
    std::vector<Tile *> possibleSpawnSpots;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile *t = &tiles[i][j];
            if (t->GetTileState() == ETileState::Empty)
            {
                if (t->GetIntValue() == 0)
                {
                    possibleSpawnSpots.push_back(t);
                }
            }
        }
    }

    auto size = possibleSpawnSpots.size();
    if (size > 0)
    {
        int index = GetRandomValue(1, size) - 1;
        possibleSpawnSpots[index]->CreateTileFromEmpty();
    }
    else
    {
        // GAME OVER
    }
}

void Grid::UpdateTiles()
{
    bool allTilesStationary = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile *tile = &tiles[i][j];
            ETileState state = tile->UpdateTile();
            if (state == ETileState::Moving || state == ETileState::MovingToMerge)
            {
                allTilesStationary = false;
                readyForGridReconciliation = true;
                eGridState = EGridState::Moving;
            }
        }
    }

    if (allTilesStationary)
    {
        if (readyForGridReconciliation)
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    Tile *thisTile = &tiles[i][j];
                    int this_i = thisTile->GetI();
                    int this_j = thisTile->GetJ();

                    if (i != this_i || j != this_j)
                    {
                        tiles[this_i][this_j] = *thisTile;
                        tiles[i][j] = Tile(i, j);
                    }
                }
            }
            readyForGridReconciliation = false;

            SpawnNewTile();
            eGridState = EGridState::Stationary;
        }
    }
}

void Grid::SetTileOnTilesGrid(int i, int j, Tile *t)
{
    tiles[i][j] = *t;
    t->SetI(i);
    t->SetJ(j);
}

void Grid::PrintOutTileData()
{
    std::cout << "Starting print" << std::endl
              << std::endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Tile *tile = &tiles[i][j];
            tile->PrintOutTileData();
        }
    }
    std::cout << std::endl
              << "~~~~~~~~~~~~~~" << std::endl;
}

void Grid::PrintTileDataNew()
{
    std::cout << "Starting print" << std::endl
              << std::endl;
    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            Tile *thisTile = &tiles[a][b];
            if (thisTile->GetTileState() != ETileState::Empty)
            {
                std::cout << "tiles[a][b], a: " << a << ", b: " << b << ", i: " << thisTile->GetI() << ", j: " << thisTile->GetJ() << ", v: " << thisTile->GetIntValue()
                          << ", " << "ETileState: " << thisTile->GetTileState() << std::endl;
            }
        }
    }

    std::cout << std::endl;
}

Tile *Grid::VerifyValidCoordinates(int a, int b, Tile *tileToCheck)
{
    return (a < 0 || a > 3 || b < 0 || b > 3) ? nullptr : tileToCheck;
}

ETileState Grid::evaluateMoveTilesStateBehaviour(Tile *t1, Tile *t2)
{
    if (t1 != t2)
    {
        if ((t1->GetIntValue() == t2->GetIntValue()))
        {
            return ETileState::MovingToMerge;
        }
    }
    return ETileState::Moving;
}

bool Grid::tilesCanMerge(Tile *t1, Tile *t2)
{
    if (t1 != t2)
    {
        if ((t1->GetIntValue() == t2->GetIntValue()))
        {
            return true;
        }
    }
    return false;
}
