#include "GameScene.h"
#include <vector>

float frame = 0;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 격자 그리기
    drawGridMap();
    
    // 버튼
    auto label1 = Label::createWithSystemFont("Left", "arial", 10);
    auto label2 = Label::createWithSystemFont("Right", "arial", 10);
    auto label3 = Label::createWithSystemFont("Rotate", "arial", 10);
    
    auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(GameScene::leftBtnCallback, this));
    auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(GameScene::rightBtnCallback, this));
    auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(GameScene::rotateBtnCallback, this));
    
    Menu* menu = Menu::create(item1, item2, item3, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Point(300, 100));
    this->addChild(menu, 1);
    this->scheduleUpdate();
    
    // 테트로미노 생성하고 그리기
    drawTetromino();
    return true;
}

void GameScene::update(float fDelta)
{
    frame += fDelta;
    if(frame < FALL_DELAY_TIME)
    {
        return;
    }
    frame -= FALL_DELAY_TIME;
    
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

void GameScene::drawGridMap()
{
    // 가로줄
    for (int i = 0; i <= MAX_MAP; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(0, i * BLOCK_SIZE),
            Vec2(BLOCK_SIZE * MAX_MAP, i * BLOCK_SIZE),
            Color4F(Color3B::WHITE, 1));

        this->addChild(draw, 1);
    }

    // 세로줄
    for (int i = 0; i <= MAX_MAP; i++)
    {
        auto draw = DrawNode::create();
        draw->drawLine(
            Vec2(i * BLOCK_SIZE, 0),
            Vec2(i * BLOCK_SIZE, BLOCK_SIZE * MAX_MAP),
            Color4F(Color3B::WHITE, 1));
        this->addChild(draw, 1);
    }
}

void GameScene::drawTetromino()
{
    cur_tetro = gm.createTetromino();
    for (int i = 0; i < 4; ++i)
    {
        cur_tetro->block[i].sprite->setAnchorPoint(Point(0, 0));
        cur_tetro->block[i].sprite->setPosition(150 + cur_tetro->block[i].x * BLOCK_SIZE, cur_tetro->block[i].y * BLOCK_SIZE);
        this->addChild(cur_tetro->block[i].sprite);
        board[cur_tetro->block[i].y][cur_tetro->block[i].x] = 2;
    }
}

bool GameScene::downCheck()
{
    for (int i = 0; i < 4; ++i)
    {
        int cy = cur_tetro->block[i].y;
        // 제일 밑칸이거나 밑에 블록이 있다면
        if (cy == 0 || board[cy-1][cur_tetro->block[i].x] == BoardInfo::obstacle)
        {
            // 부딪히므로 떨어지는 테트로미노(2)를 (1)로 바꿔주기
            for (int j = 0; j < 4; ++j)
            {
                board[cur_tetro->block[j].y][cur_tetro->block[j].x] = BoardInfo::obstacle;
            }
            return true;
        }
    }
    return false;
}

void GameScene::fall()
{
    for (int i = 0; i < 4; ++i)
    {
        auto moveDown = MoveBy::create(0, Point(0, -BLOCK_SIZE));
        cur_tetro->block[i].sprite->runAction(moveDown);
        
        // 보드 수정
        int cx = cur_tetro->block[i].x;
        int cy = cur_tetro->block[i].y;
        board[cy][cx] = BoardInfo::None;
        board[cy - 1][cx] = BoardInfo::fallingblock;
        cur_tetro->block[i].y -= 1;
    }
}

void GameScene::leftBtnCallback(Ref* sender)
{
    cur_tetro->moveLeft(board);
}

void GameScene::rightBtnCallback(Ref* sender)
{
    cur_tetro->moveRight(board);
}

void GameScene::rotateBtnCallback(Ref* sender)
{
    cur_tetro->Rotate(board, cur_tetro->rotateidx);
}
