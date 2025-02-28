#pragma once

#include <raylib.h>
#include <map>

extern const Color spawnColour;

extern const Color _2;    // = {238, 228, 218, 255};
extern const Color _4;    // = {235, 216, 182, 255};
extern const Color _8;    // = {242, 177, 119, 255};
extern const Color _16;   // = {245, 143, 90, 255};
extern const Color _32;   // = {245, 117, 87, 255};
extern const Color _64;   // = {245, 90, 54, 255};
extern const Color _128;  // = {243, 207, 82, 255};
extern const Color _256;  // = {244, 204, 74, 255};
extern const Color _512;  // = {245, 200, 62, 255};
extern const Color _1024; // = {246, 196, 56, 255};
extern const Color _2048; // = {247, 192, 50, 255};
extern const Color _4096; // = {248, 186, 44, 255};

extern const Color Text_Brown; // = {117, 100, 82, 255};
extern const Color Text_White; // = {255, 255, 255, 255};

extern std::map<int, Color> tileColourMap;
extern std::map<int, Color> tileTextColourMap;

extern std::map<int, float> textSizeMap;