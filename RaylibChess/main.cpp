#include <iostream>
#include <raylib.h>
#include "conf.h"
#include "enums.h"
#include "screen.h"
#include "square.h"
// #include <vector>

using namespace std;

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess");
    SetTargetFPS(60);

    bool debugBoard = false;
    Screen screen = Screen(debugBoard);

    while (WindowShouldClose() == false)
    {

        Vector2 mousePosF = GetMousePosition();
        int mousePosX = static_cast<int>(mousePosF.x);
        int mousePosY = static_cast<int>(mousePosF.y);

        bool mousePress = IsMouseButtonPressed(0);
        if (mousePress)
        {
            if (screen.GetScreenMode() != EScreenMode::Checkmate)
            {
                screen.EvaluateClickedSquare(mousePosX, mousePosY);
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        screen.DrawGameBoard();

        EndDrawing();
    }

    screen.UnloadAllSprites();
    CloseWindow();
}