#pragma once
#include "Headers.h"
#include "Tetromino.h"
#include "GameManager.h"

class GameScene : public Layer
{
public:
    int board[MAX_ROW][MAX_COL];
    Sprite* cur_block;
    Tetromino* cur_tetro;
    static Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    
private:
    GameManager gm;
    
    void update(float fDelta) override;
    void drawGridMap();
    void drawTetromino();
    
    void leftBtnCallback(Ref* sender);
    void rightBtnCallback(Ref* sender);
    void rotateBtnCallback(Ref* sender);
    
    bool downCheck();
    void fall();
};
