#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init(void)
{
    _tf = new TutorialField();
    _tf->init();

    _item = new Item;
    _item->init(WINSIZE_X / 2 + 300, WINSIZE_Y / 2  + 180);

    _itemList.push_back(_item);

    _nextStage = 0;
    _temp = 0;
    _isInven = false;
    _isRespawn = true;

    SOUNDMANAGER->addWaveFileWithKey("zone", "Resources/Sound/ZONE_INFO.wav");

    return S_OK;
}

void Tutorial::release(void)
{
    SAFE_DELETE(_tf);
    SAFE_DELETE(_item);
}

void Tutorial::update(void)
{
    if (!_isInven)
    {
        PLAYER->playerAction();
        PLAYER->playerMove();
    }

    if (!_itemList.empty())
    {
        _itemList[0]->update();

        RECT _rt;
        if (IntersectRect(&_rt, &PLAYER->getHitBox(), &_item->getRect()))
        {
            _itemList[0]->setPick(true);
            PLAYER->setCollect(true);

            if (PLAYER->getCollected())
            {
                _itemList.pop_back();
                INVENTORY->addItem(ROSARY, { "Item1", "비둘기 뼈",
                    {"구멍이 뚫린 새의 두개골.", "부서지기 쉬운 이 두개골은", "참회자의 방어력을 약간 올려준다."}, false });
            }
        }
        else
        {
            _itemList[0]->setPick(false);
            PLAYER->setCollect(false);
        }
    }
    else
        PLAYER->setCollect(false);

    _tf->update();
    // 중력
    //if (!PLAYER->getFixed())
    
    //if (!PLAYER->getState()[JUMP])
    //    PLAYER->setPosY(PLAYER->getPosY() + 8.0f);

    if (PLAYER->getHitBox().left <= 0)
    {
        PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
    }

    //if (PLAYER->getJumpPower() 

    cout << PLAYER->getJumpPower() << endl;
    cout << "isGround? " << PLAYER->getGround() << endl;
    cout << "is Jumping? " << PLAYER->getState()[JUMP] << endl;
    for (int i = PLAYER->getHitBox().left; i <= PLAYER->getHitBox().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("tutorial_map_collision")->getMemDC(),
            i, PLAYER->getHitBox().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        COLORREF color2 = GetPixel(IMAGEMANAGER->findImage("tutorial_map_collision")->getMemDC(),
            i, PLAYER->getHitBox().bottom - 2);

        int r2 = GetRValue(color2);
        int g2 = GetGValue(color2);
        int b2 = GetBValue(color2);


        if ((r == 255 && g == 0 && b == 255))           
        {
            //while (r2 == 255 && g2 == 0 && b2 == 255)
            //{
            //    PLAYER->setPosY(PLAYER->getPosY() + 1.0);
            //}

            PLAYER->setGround(true);
            
            break;
        }
        PLAYER->setGround(false);    
        //PLAYER->setPosY(PLAYER->getPosY() + 1.0);

    }
    if (PLAYER->getCenterX() > WINSIZE_X)
        _nextStage = 1;

    if (KEYMANAGER->isOnceKeyDown('I'))
    {
        _isInven = true;
        INVENTORY->setOut(false);
    }
    if (_isInven)
    {
        INVENTORY->update();

        if (INVENTORY->getOut())
        {
            _isInven = false;
        }
    }
}

void Tutorial::render(void)
{
    _tf->render(getMemDC());

    if (!_itemList.empty())
        _itemList[0]->showItem(getMemDC());

    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());

    if (_isInven)
    {
        INVENTORY->render(getMemDC());
    }
}
