#pragma once
#include "tile.h"

enum class EGridState
{
    Stationary,
    Moving,
};

class Grid
{
public:
    Grid(bool background);

    Tile getTile(int i, int j);
    void DrawGrid();
    void DrawBackgroundGrid();
    void ProcessMovement(EMovement dir);
    void UpdateTiles();
    void SetTileOnTilesGrid(int i, int j, Tile *t);

    // Debug
    void PrintOutTileData();
    void PrintTileDataNew();

private:
    bool readyForGridReconciliation = false;
    Tile tiles[4][4];
    Tile backgroundTiles[4][4];
    Tile *VerifyValidCoordinates(int a, int b, Tile *tileToCheck);
    ETileState evaluateMoveTilesStateBehaviour(Tile *t1, Tile *t2);
    bool tilesCanMerge(Tile *t1, Tile *t2);
    EGridState eGridState = EGridState::Stationary;

    void RunMovementChecks(Tile *t, int i, int j, EMovement dir);
    void SpawnNewTile();
};