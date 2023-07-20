#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init(void)
{
    _pl = new Player();
    _pl->init(88, 484);

    _tf = new TutorialField();
    _tf->init();

    _item = new Item;
    _item->init(WINSIZE_X / 2, WINSIZE_Y / 2  + 180);

    _itemList.push_back(_item);

    _nextStage = 0;
    _isInven = false;

    return S_OK;
}

void Tutorial::initPlayer(int x, int y)
{
    this->_pl->init(x, y);
}

void Tutorial::release(void)
{
    SAFE_DELETE(_pl);
    SAFE_DELETE(_tf);
    SAFE_DELETE(_item);
}

void Tutorial::update(void)
{
    if (!_isInven)
    {
        _pl->playerAction();
        _pl->playerMove();
    }

    if (!_itemList.empty())
    {
        _itemList[0]->update();

        RECT _rt;
        if (IntersectRect(&_rt, &_pl->getRect(), &_item->getRect()))
        {
            _itemList[0]->setPick(true);
            _pl->setCollect(true);

            if (_pl->getCollected())
            {
                _itemList.pop_back();
                INVENTORY->addItem(ROSARY, { "Item1", "비둘기 뼈", 
                    {"구멍이 뚫린 새의 두개골.", "부서지기 쉬운 이 두개골은", "참회자의 방어력을 약간 올려준다."}, false });
            }
        }
        else
        {
            _itemList[0]->setPick(false);
            _pl->setCollect(false);
        }
    }

    if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5.0f);

    for (int i = _pl->getRect().left; i <= _pl->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("tutorial_map_collision")->getMemDC(),
            i, _pl->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            _pl->setGround(true);
            break;
        }
        _pl->setGround(false);
    }

    if (_pl->getRect().left > WINSIZE_X)
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

    _pl->renderPlayer(getMemDC());
    _pl->renderProfile(getMemDC());

    if (_isInven)
    {
        INVENTORY->render(getMemDC());
    }
}
