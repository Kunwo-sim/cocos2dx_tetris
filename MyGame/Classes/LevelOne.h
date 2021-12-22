#pragma once
#include "Headers.h"
#include "Tetromino.h"
#include "GameManager.h"

class LevelOne : public Layer
{
public:
    int board[22][10];
    Sprite* cur_block;
    Tetromino* cur_tetro;
    static Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(LevelOne);
    
private:
    GameManager gm;
    
    void update(float fDelta) override;
    void drawGridMap();
    void drawTetromino();
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) override;
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;
    
    bool downCheck();
    void fall();
};
