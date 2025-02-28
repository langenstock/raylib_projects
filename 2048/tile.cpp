#include "tile.h"
#include <string>
#include <iostream>

Tile::Tile()
{
}

Tile::Tile(int i, int j, int v, ETileState eTileState)
{
    this->i = i;
    this->j = j;

    x = GRID_START_X + (TILE_SIZE * i);
    y = GRID_START_Y + (TILE_SIZE * j);

    value = v;
    this->eTileState = eTileState;

    tileTextColour = tileTextColourMap[v];
    tileColour = tileColourMap[v];
    tileTextSize = textSizeMap[v];
}

Tile::Tile(int i, int j) // Used for Background Tiles
{
    this->i = i;
    this->j = j;

    x = GRID_START_X + (TILE_SIZE * i);
    y = GRID_START_Y + (TILE_SIZE * j);

    value = 0;

    eTileState = ETileState::Empty;
}

void Tile::CreateTileFromEmpty()
{
    value = 2;
    eTileState = ETileState::Stationary;
    tileColour = spawnColour;
    tileTextColour = tileTextColourMap[2];
    tileTextSize = textSizeMap[2];
}

int Tile::GetX()
{
    return x;
}

int Tile::GetY()
{
    return y;
}

int Tile::GetI()
{
    return i;
}

int Tile::GetJ()
{
    return j;
}

void Tile::SetI(int i)
{
    this->i = i;
}

void Tile::SetJ(int j)
{
    this->j = j;
}

int Tile::GetIntValue()
{
    return value;
}

const char *Tile::GetValue()
{
    if (value == 0)
    {
        return "";
    }
    else
    {
        std::string str = std::to_string(value);

        const char *cstr = str.c_str();
        std::cout << cstr << std::endl;
        return cstr;
    }

    return nullptr;
}

void Tile::DoubleValue()
{
    value *= 2;
    tileColour = tileColourMap[value];
    tileTextColour = tileTextColourMap[value];
    tileTextSize = textSizeMap[value];
}

int Tile::GetDestI()
{
    return destination_i;
}

int Tile::GetDestJ()
{
    return destination_j;
}

int Tile::GetDestX()
{
    return destination_x;
}

int Tile::GetDestY()
{
    return destination_y;
}

float Tile::GetTextPosX()
{
    return static_cast<float>(x + 25);
}

float Tile::GetTextPosY()
{
    return static_cast<float>(y + 25);
}

void Tile::SetTileDestination(int dest_i, int dest_j, ETileState newState)
{
    destination_i = dest_i;
    destination_j = dest_j;
    destination_x = GRID_START_X + (TILE_SIZE * destination_i);
    destination_y = GRID_START_Y + (TILE_SIZE * destination_j);

    eTileState = newState;
}

ETileState Tile::GetTileState()
{
    return eTileState;
}

void Tile::SetTileState(ETileState state)
{
    eTileState = state;
}

ETileState Tile::UpdateTile()
{
    if (eTileState == ETileState::Moving || eTileState == ETileState::MovingToMerge)
    {
        if (destination_x != x)
        {
            x += ((destination_x - x) > 0) ? MOVE_SPEED : -MOVE_SPEED;
        }

        if (destination_y != y)
        {
            y += ((destination_y - y) > 0) ? MOVE_SPEED : -MOVE_SPEED;
        }

        if (destination_x == x && destination_y == y)
        {
            eTileState = ETileState::Stationary;

            i = destination_i;
            j = destination_j;
        }
    }

    if (value == 2)
    {
        int r = tileColourMap[2].r;
        if (tileColour.r < r)
        {
            tileColour.r += (r - tileColour.r) * 0.2;
            tileColour.g += (tileColourMap[2].g - tileColour.g) * 0.2;
            tileColour.b += (tileColourMap[2].b - tileColour.b) * 0.2;
        }
    }

    return eTileState;
}

Color Tile::getTileColour()
{
    return tileColour;
}

Color Tile::getTileTextColour()
{
    return tileTextColour;
}

float Tile::getTextSize()
{
    return tileTextSize;
}

void Tile::PrintOutTileData()
{
    std::cout << "Tile at i: " << i << ", j: " << j << ", value: " << value << std::endl;
}
