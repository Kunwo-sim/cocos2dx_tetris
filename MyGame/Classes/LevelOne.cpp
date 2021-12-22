#include "LevelOne.h"
#include <vector>

float frame = 0;



Scene* LevelOne::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LevelOne::create();
    scene->addChild(layer);
    
    return scene;
}

bool LevelOne::init()
{
    if (!Layer::init())
    {
        return false;
    }

    
    // 격자 그리기
    drawGridMap();
    
    // listener 세팅
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(LevelOne::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(LevelOne::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//    this->setKeyboardEnabled(true);
    
    this->scheduleUpdate();
    
    // 테트로미노 생성하고 그리기
    drawTetromino();
    return true;
}

void LevelOne::update(float fDelta)
{
    frame += fDelta;
    if(frame < 0.3f)
    {
        return;
    }
    frame -= 0.3f;
    // 현재 테트로미노가 다음에 충돌하면 새 블록 생성
    if(downCheck())
    {
        drawTetromino();
    }
    // 충돌하지 않으면 떨어지기
    else
    {
        fall();
    }
}

void LevelOne::drawGridMap()
{
    // 가로줄
    for (int i = 0; i <= 20; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(0, i * BLOCK_SIZE),
            Vec2(BLOCK_SIZE * 20, i * BLOCK_SIZE),
            Color4F(Color3B::WHITE, 1));

        this->addChild(draw);
    }

    // 세로줄
    for (int i = 0; i <= 20; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(i * BLOCK_SIZE, 0),
            Vec2(i * BLOCK_SIZE, BLOCK_SIZE * 20),
            Color4F(Color3B::WHITE, 1));
        this->addChild(draw);
    }
}

void LevelOne::drawTetromino()
{
    cur_tetro = gm.createTetromino();
    for (int i = 0; i < 4; ++i)
    {
        cur_tetro->block[i].sprite = Sprite::create("white.png", Rect(0, 0, BLOCK_SIZE, BLOCK_SIZE));
        cur_tetro->block[i].sprite->setAnchorPoint(Point(0, 0));
        cur_tetro->block[i].sprite->setPosition(150 + cur_tetro->block[i].x * BLOCK_SIZE, cur_tetro->block[i].y * BLOCK_SIZE);
        this->addChild(cur_tetro->block[i].sprite);
        board[cur_tetro->block[i].y][cur_tetro->block[i].x] = 2;
    }
}

bool LevelOne::downCheck()
{
    for (int i = 0; i < 4; ++i)
    {
        int cy = cur_tetro->block[i].y;
        CCLOG("%i", cy);
        if (cy == 0 || board[cy+1][cur_tetro->block[i].x] == 1)
        {
            // 부딪히므로 떨어지는 테트로미노(2)를 (1)로 바꿔주기
            for (int j = 0; j < 4; ++j)
            {
                board[cur_tetro->block[j].y][cur_tetro->block[j].x] = 1;
            }
            return true;
        }
    }
    return false;
}

void LevelOne::fall()
{
    for (int i = 0; i < 4; ++i)
    {
        auto moveDown = MoveBy::create(0, Point(0, -BLOCK_SIZE));
        cur_tetro->block[i].sprite->runAction(moveDown);
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        board[cy][cx] = 0;
        board[cy + 1][cx] = 2;
        cur_tetro->block[i].y -= 1;
    }
}


void LevelOne::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
}

void LevelOne::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
}
