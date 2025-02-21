#pragma once
#include <raylib.h>
#include <map>
#include "enums.h"

class Sprites
{
public:
    Sprites();
    Texture2D *GetTexture(ETeam eTeam, EPiece ePiece);
    void UnloadAll();

private:
    std::map<EPiece, Texture2D> whiteTexMap;
    std::map<EPiece, Texture2D> blackTexMap;
};
