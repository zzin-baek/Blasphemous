#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init(void)
{
    /*PLAYER = new Player();
    PLAYER->init(88, 484);*/

    //PLAYER->init(88, 484);

    _tf = new TutorialField();
    _tf->init();

    _item = new Item;
    _item->init(WINSIZE_X / 2 + 300, WINSIZE_Y / 2  + 180);

    _itemList.push_back(_item);

    _nextStage = 0;
    _isInven = false;
    _isRespawn = true;

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
        if (IntersectRect(&_rt, &PLAYER->getRect(), &_item->getRect()))
        {
            _itemList[0]->setPick(true);
            PLAYER->setCollect(true);

            if (PLAYER->getCollected())
            {
                _itemList.pop_back();
                INVENTORY->addItem(ROSARY, { "Item1", "��ѱ� ��",
                    {"������ �ո� ���� �ΰ���.", "�μ����� ���� �� �ΰ�����", "��ȸ���� ������ �ణ �÷��ش�."}, false });
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
    // �߷�
    //if (!PLAYER->getGround())
    PLAYER->setPosY(PLAYER->getPosY() + 5.0f);

    if (PLAYER->getRect().left <= 0)
    {
        PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
    }

    for (int i = PLAYER->getRect().left; i <= PLAYER->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("tutorial_map_collision")->getMemDC(),
            i, PLAYER->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            PLAYER->setGround(true);
            PLAYER->setPosY(PLAYER->getPosY() - 5.0f);
            break;
        }
        PLAYER->setGround(false);
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
