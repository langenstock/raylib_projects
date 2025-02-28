#include <iostream>
#include <raylib.h>
#include "grid.h"

using namespace std;

void EvaluateInput(Grid *grid);
bool hideMainGrid = false;
bool hideBackgroundGrid = false;

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2048");
    SetTargetFPS(60);

    bool background = false;
    Grid grid = Grid(background);

    background = true;
    Grid backgroundGrid = Grid(background);

    while (WindowShouldClose() == false)
    {

        BeginDrawing();
        ClearBackground(BLACK);
        EvaluateInput(&grid);
        if (!hideBackgroundGrid)
        {
            backgroundGrid.DrawBackgroundGrid();
        }
        if (!hideMainGrid)
        {
            grid.DrawGrid();
        }
        grid.UpdateTiles();

        EndDrawing();
    }

    CloseWindow();
}

void EvaluateInput(Grid *grid)
{
    int key = GetKeyPressed();
    switch (key)
    {
    case (KEY_W):
        grid->ProcessMovement(EMovement::Up);
        break;
    case (KEY_S):
        grid->ProcessMovement(EMovement::Down);
        break;
    case (KEY_A):
        grid->ProcessMovement(EMovement::Left);
        break;
    case (KEY_D):
        grid->ProcessMovement(EMovement::Right);
        break;
    case (KEY_F1):
        grid->PrintOutTileData();
        break;
    case (KEY_F2):
        hideMainGrid = !hideMainGrid;
        break;
    case (KEY_F3):
        hideBackgroundGrid = !hideBackgroundGrid;
        break;
    case (KEY_F4):
        grid->PrintTileDataNew();
        break;
    }
}