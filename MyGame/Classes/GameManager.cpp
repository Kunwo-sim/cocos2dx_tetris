#include "GameManager.h"

Tetromino* GameManager::createTetromino()
{
    // 랜덤 테트로미노 생성
    srand(time(NULL));
    int randint = rand() % 4;
    Tetromino* tetromino = new Tetromino();
    int _x = tetromino->originX;
    int _y = tetromino->originY;
    int delta_idx = 0;
    int delta_shape[8] = {0};
    switch (randint)
    {
        // J 블록
        case 0:
        {
            delta_shape[3] = 1;
            delta_shape[4] = delta_shape[5] = delta_shape[7] = -1;
            break;
        }
        // I 블록
        case 1:
        {
            delta_shape[7] = 2;
            delta_shape[5] = 1;
            delta_shape[3] = -1;
            break;
        }
        // O 블록
        case 2:
        {
            delta_shape[2] = delta_shape[5] = delta_shape[6] = delta_shape[7] = 1;
            break;
        }
        // h 블록
        case 3:
        {
            delta_shape[4] = delta_shape[7] = 1;
            delta_shape[2] = -1;
        }
    }
    
    for (int i = 0; i < 4; ++i)
    {
        tetromino->block[i].x = _x + delta_shape[delta_idx];
        tetromino->block[i].y = _y + delta_shape[delta_idx + 1];
        delta_idx += 2;
    }
    return tetromino;
}
