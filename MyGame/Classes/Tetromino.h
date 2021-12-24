#pragma once
#include "Headers.h"

struct Block
{
    Sprite* sprite;
    // 중앙 블록에서 차이나는 만큼
    int x;
    int y;
};

class Tetromino
{
public:
    Block block[4];
    
    int rotateidx = 0;
    int shape = 0;
    int originX = START_X;
    int originY = START_Y;
    
    void moveLeft(int board[][MAX_COL]);
    void moveRight(int board[][MAX_COL]);
    void Rotate(int board[][MAX_COL], int r_idx);
    
private:
};
