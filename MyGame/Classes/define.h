#pragma once
const float BLOCK_SIZE = 15.0F;
const float FALL_DELAY_TIME = 0.3F;

const int MAX_COL = 10;
const int MAX_ROW = 22;
const int MAX_MAP_ROW = 20;
const int MAX_MAP = 20;
const int START_X = 5;
const int START_Y = 18;

const int delta_rotate[28][8] =
{
    // J
    {1, 0, 1, 0, 0, -1, 0, 1},
    {0, 2, -1, -1, 0, 0, 1, 1},
    {0, -1, 0, 1, -1, 0, -1, 0},
    {-1, -1, 0, 0, 1, 1, 0, -2},
    
    // I
    {2, 1, 1, 0, 0, -1, -1, -2},
    {-2, -1, -1, 0, 0, 1, 1, 2},
    {2, 1, 1, 0, 0, -1, -1, -2},
    {-2, -1, -1, 0, 0, 1, 1, 2},
    
    // O
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    
    // H
    {0, 0, 0, 0, 0, 0, -1, -1},
    {-1, -1, 0, 1, 0, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, -1, 1, 1},
    
    // L
    {1, 0, 1, 0, 0, -1, 0, 1},
    {0, 2, -1, -1, 0, 0, 1, 1},
    {0, -1, 0, 1, -1, 0, -1, 0},
    {-1, -1, 0, 0, -1, -1, 0, -2},
    
    // S
    {1, 2, 0, 0, 1, 1, 0, -1},
    {-1, -2, 0, 0, -1, -1, 0, 1},
    {1, 2, 0, 0, 1, 1, 0, -1},
    {-1, -2, 0, 0, -1, -1, 0, 1},
    
    // Z
    {1, -1, 0, -2, 1, 1, 0, 0},
    {-1, 1, 0, 2, -1, -1, 0, 0},
    {1, -1, 0, -2, 1, 1, 0, 0},
    {-1, 1, 0, 2, -1, -1, 0, 0},
};

enum BoardInfo
{
    None,
    obstacle,
    fallingblock,
    tempblock
};

enum Shape
{
    J,
    I,
    O,
    H,
    L,
    S,
    Z
};
