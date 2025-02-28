#pragma once

#include "conf.cpp"
#include "font.cpp"
#include "colours.h"

const Font font = LoadFontEx("fonts/PER.TTF", 48, 0, 0);

enum ETileState
{
    Stationary,
    Moving,
    MovingToMerge,
    Empty,
};

enum EMovement
{
    Up,
    Down,
    Left,
    Right
};

class Tile
{
public:
    Tile();
    Tile(int i, int j, int v, ETileState eTileState);
    Tile(int i, int j);

    void CreateTileFromEmpty();

    int GetX();
    int GetY();
    int GetI();
    int GetJ();
    void SetI(int i);
    void SetJ(int j);
    int GetIntValue();
    void DoubleValue();
    const char *GetValue();
    int GetDestI();
    int GetDestJ();
    int GetDestX();
    int GetDestY();
    float GetTextPosX();
    float GetTextPosY();
    ETileState GetTileState();

    void SetTileDestination(int dest_i, int dest_j, ETileState newState);
    void SetTileState(ETileState state);
    ETileState UpdateTile();
    Color getTileColour();
    Color getTileTextColour();
    float getTextSize();

    // Debug
    void PrintOutTileData();

private:
    int i;
    int j;
    int x;
    int y;
    ETileState eTileState;
    int value;

    int destination_i;
    int destination_j;
    int destination_x;
    int destination_y;
    Color tileTextColour = tileTextColourMap[2];
    Color tileColour;
    float tileTextSize = textSizeMap[2];
};