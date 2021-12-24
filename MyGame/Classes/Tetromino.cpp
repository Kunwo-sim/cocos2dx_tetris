#include "Tetromino.h"

void Tetromino::moveLeft(int board[][MAX_COL])
{
    // 움직일 수 있는지 체크
    for (int i = 0; i < 4; ++i)
    {
        if (board[block[i].y][block[i].x-1] == BoardInfo::obstacle || block[i].x == 0)
        {
            return;
        }
    }
    
    for (int i = 0; i < 4; ++i)
    {
        block[i].x -= 1;
        
        Action* Left = MoveBy::create(0, Point(-BLOCK_SIZE, 0));
        block[i].sprite->runAction(Left);
    }
}

void Tetromino::moveRight(int board[][MAX_COL])
{
    // 움직일 수 있는지 체크
    for (int i = 0; i < 4; ++i)
    {
        if (board[block[i].y][block[i].x+1] == BoardInfo::obstacle || block[i].x == MAX_COL-1)
        {
            return;
        }
    }
    
    for (int i = 0; i < 4; ++i)
    {
        block[i].x += 1;
        
        Action* Right = MoveBy::create(0, Point(BLOCK_SIZE, 0));
        block[i].sprite->runAction(Right);
    }
}

void Tetromino::Rotate(int board[][MAX_COL], int r_idx)
{
    // 회전 가능한지 확인
    for(int i = 0; i < 4; ++i)
    {
        int dx = delta_rotate[4 * shape + r_idx][2 * i];
        int dy = delta_rotate[4 * shape + r_idx][2 * i + 1];
        int nx = block[i].x + dx;
        int ny = block[i].y + dy;
        if (nx < 0 || nx >= MAX_COL || ny < 0 || board[ny][nx] == BoardInfo::obstacle)
            return;
    }
    // 회전
    for (int i = 0; i < 4; ++i)
    {
        int dx = delta_rotate[4 * shape + r_idx][2 * i];
        int dy = delta_rotate[4 * shape + r_idx][2 * i + 1];
        block[i].x += dx;
        block[i].y += dy;

        Action* Rotate = MoveBy::create(0, Point(dx * BLOCK_SIZE, dy * BLOCK_SIZE));
        block[i].sprite->runAction(Rotate);
    }
    rotateidx += 1;
    rotateidx %= 4;
}
