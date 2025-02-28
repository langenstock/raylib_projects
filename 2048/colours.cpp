#include "colours.h"

const Color spawnColour = {138, 128, 118, 255};

const Color _2 = {238, 228, 218, 255};
const Color _4 = {235, 216, 182, 255};
const Color _8 = {242, 177, 119, 255};
const Color _16 = {245, 143, 90, 255};
const Color _32 = {245, 117, 87, 255};
const Color _64 = {245, 90, 54, 255};
const Color _128 = {243, 207, 82, 255};
const Color _256 = {244, 204, 74, 255};
const Color _512 = {245, 200, 62, 255};
const Color _1024 = {246, 196, 56, 255};
const Color _2048 = {247, 192, 50, 255};
const Color _4096 = {248, 186, 44, 255};

const Color Text_Brown = {117, 100, 82, 255};
const Color Text_White = {255, 255, 255, 255};

std::map<int, Color> tileColourMap = {
    {2, _2},
    {4, _4},
    {8, _8},
    {16, _16},
    {32, _32},
    {64, _64},
    {128, _128},
    {256, _256},
    {512, _512},
    {1024, _1024},
    {2048, _2048},
    {4096, _4096},
};

std::map<int, Color> tileTextColourMap = {
    {2, Text_Brown},
    {4, Text_Brown},
    {8, Text_White},
    {16, Text_White},
    {32, Text_White},
    {64, Text_White},
    {128, Text_White},
    {256, Text_White},
    {512, Text_White},
    {1024, Text_White},
    {2048, Text_White},
    {4096, Text_White},
};

std::map<int, float> textSizeMap = {
    {2, 48.0f},
    {4, 48.0f},
    {8, 48.0f},
    {16, 48.0f},
    {32, 48.0f},
    {64, 48.0f},
    {128, 40.0f},
    {256, 40.0f},
    {512, 40.0f},
    {1024, 24.0f},
    {2048, 24.0f},
    {4096, 24.0f},
};