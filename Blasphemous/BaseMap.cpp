#include "Stdafx.h"
#include "BaseMap.h"

HRESULT BaseMap::init(void)
{
    _pl = new Player;
    _pl->init(120, 315);

    _bf = new BattleField;
    _bf->init();

    _ac = new Acolyte;
    _ac->init();

    _item = new Item;
    _item->init(1050, 135);

    _acolyteList.push_back(_ac);
    _itemList.push_back(_item);

    _nextStage = _preStage = _cnt = 0;
    _isInven = false;
    return S_OK;
}

void BaseMap::release(void)
{
    SAFE_DELETE(_pl);
    SAFE_DELETE(_bf);
    SAFE_DELETE(_ac);
    SAFE_DELETE(_item);
}

void BaseMap::update(void)
{
    if (!_isInven)
    {
        _pl->playerAction();
        _pl->playerMove();
        if(!_acolyteList.empty())
            _acolyteList[0]->move();
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
                INVENTORY->addItem(HERITAGE, { "Item2", "설명", "어쩌구", false });
            }
        }
        else
        {
            _itemList[0]->setPick(false);
            _pl->setCollect(false);
        }
    }

    if (_pl->getRect().left >= WINSIZE_X)
        _nextStage = 1;
    else if (_pl->getRect().right <= 0)
        _preStage = 1;

    // 중력
    if (!_pl->getGround() && !_pl->getFixed())
        _pl->setPosY(_pl->getPosY() + 5.0f);

    // 카메라 이동
    if (_pl->getCenterX() > WINSIZE_X / 2 && _bf->getX() + 1280 < 2000)
    {
        _bf->setX(_bf->getX() + 4.0f);
        _pl->setPosX(_pl->getPosX() - 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_ac->getPosX() - 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() - 4);

    }
    if (_pl->getLeft() && _pl->getCenterX() < WINSIZE_X / 2 + 10)
    {
        _bf->setX(_bf->getX() - 4.0f);
        _pl->setPosX(_pl->getPosX() + 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_ac->getPosX() + 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() + 4);
    }
    if (_pl->getRect().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        _pl->setPosY(_pl->getPosY() + 2.0f);
        _bf->setY(_bf->getY() - 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_ac->getPosY() + 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() + 2);
    }
    if (_pl->getRect().top > WINSIZE_Y / 2 + 50 && (_bf->getY() + 720 < 938))
    {
        _pl->setPosY(_pl->getPosY() - 2.0f);
        _bf->setY(_bf->getY() + 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_ac->getPosY() - 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() - 2);
    }

    _bf->rectMove();

    RECT _rt;
    if (PtInRect(&_bf->getLadder(), { (_pl->getRect().left + _pl->getRect().right) / 2,
        _pl->getRect().bottom - 20 }))
    {
        _pl->setHold(true);
    }
    else
    {
        _pl->setHold(false);
        _pl->setFixed(false);
    }

    // 픽셀 충돌
    for (int i = _pl->getRect().left; i <= _pl->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + i, _bf->getY() + _pl->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            _pl->setGround(true);
            //_pl->setPosY(_pl->getPosY() - 1.0f);
            break;
        }
        _pl->setGround(false);
    }

    for (int i = _pl->getRect().top; i < _pl->getRect().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _pl->getRect().left, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            _pl->setPosX(_pl->getPosX() + 4.0f);
            break;
        } 
    }

    for (int i = _pl->getRect().top; i < _pl->getRect().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _pl->getRect().right, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);
        
        if ((r == 255 && g == 0 && b == 255))
        {
            _pl->setPosX(_pl->getPosX() - 4.0f);
            break;
        }
    }

    if (!_acolyteList.empty())
    {
        // acolyte 픽셀충돌
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _acolyteList[0]->getPosX() + 80, _bf->getY() + _acolyteList[0]->getPosY());

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            _acolyteList[0]->setLeft(true);
        }

        color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _acolyteList[0]->getPosX() + 30, _bf->getY() + _acolyteList[0]->getPosY() - 50);

        r = GetRValue(color);
        g = GetGValue(color);
        b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            if (!_acolyteList[0]->getState()[ATTACK])
                _acolyteList[0]->setLeft(false);
            else
            {
                _acolyteList[0]->setPosX(_acolyteList[0]->getRect().left);
                _acolyteList[0]->setPosY(_acolyteList[0]->getRect().bottom);
            }
        }

        // 전투
        for (int i = 0; i < 2; i++)
        {
            if (IntersectRect(&_rt, &_pl->getRect(), &_acolyteList[0]->getBoundary(i)))
            {

                if (_ac->isEmpty())
                {
                    _acolyteList[0]->setAction("Acolyte_attack");
                    _acolyteList[0]->setState(IDLE_ENEMY, false);
                    _acolyteList[0]->setState(ATTACK_ENEMY, true);
                    _acolyteList[0]->addAction("Acolyte_attack");
                    _acolyteList[0]->addAction("Acolyte_idle");

                    if (i == 0)
                    {
                        _acolyteList[0]->setLeft(true);
                        _acolyteList[0]->setX(_acolyteList[0]->getMaxFrame());
                    }
                    else
                    {
                        _acolyteList[0]->setLeft(false);
                        _acolyteList[0]->setX(0);

                    }
                }
            }
        }
        if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &_pl->getRect())
            && _acolyteList[0]->getState()[ATTACK_ENEMY] && !_pl->getState()[PARRY])
        {
            if (!_pl->getState()[HIT] && _acolyteList[0]->canAttack())
            {
                _pl->setState(HIT, true);
                _pl->setHP(_pl->getHP() - 5);
            }
        }
        else if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &_pl->getRect()) && _pl->getState()[PARRY])
        {
            _pl->addAction("PARRY_SUCCESS");
        }

        if (IntersectRect(&_rt, &_acolyteList[0]->getRect(), &_pl->getRect()) && _pl->getState()[ATTACK])
        {
            if (!_acolyteList[0]->getState()[HIT_ENEMY])
            {
                _acolyteList[0]->setState(HIT_ENEMY, true);
                //_ac->addAction("Acolyte_hit");


                _acolyteList[0]->setHP(_acolyteList[0]->getHP() - 10);
            }
        }
        if (_acolyteList[0]->getHP() < 0)
        {
            _acolyteList.pop_back();
        }
    }

    //인벤토리?
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

void BaseMap::render(void)
{
    _bf->render(getMemDC());
    
    if (!_itemList.empty())
        _itemList[0]->showItem(getMemDC());
    if (!_acolyteList.empty())
        _acolyteList[0]->render(getMemDC());

    _pl->renderPlayer(getMemDC());
    _pl->renderProfile(getMemDC());

    if (_isInven)
    {
        INVENTORY->render(getMemDC());
    }
}