#include "Stdafx.h"
#include "BaseMap.h"

HRESULT BaseMap::init(void)
{
    //PLAYER = new Player;
    PLAYER->init(120, 315);

    _bf = new BattleField;
    _bf->init();

    _ac = new Acolyte;
    _ac->init();

    _item = new Item;
    _item->init(1050, 135);

    _acolyteList.push_back(_ac);
    _itemList.push_back(_item);

    _nextStage = _preStage = _cnt = _term = 0;
    _isInven = false;
    return S_OK;
}

void BaseMap::release(void)
{
    SAFE_DELETE(_bf);
    SAFE_DELETE(_ac);
    SAFE_DELETE(_item);
}

void BaseMap::update(void)
{
    if (!_isInven)
    {
        PLAYER->playerAction();
        PLAYER->playerMove();
        if(!_acolyteList.empty())
            _acolyteList[0]->move();
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
                INVENTORY->addItem(HERITAGE, { "Item2", "꿈결의 죄의 장막",
                    {"열정적인 고해의 증거인", "노란색 직물. 고문당한 영혼", "앞에 다가가면 파르르 떨리며", 
                    "더 이상 말할 수 없는 자들의", "목소리를 들을 수 있게 된다." }, false });
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

    if (PLAYER->getCenterX() > WINSIZE_X)
    {
        _nextStage = 1;
    }
    else if (PLAYER->getCenterX() < 0)
    {
        _nextStage = 0;
        _preStage = 1;
    }

    // 중력
    if (!PLAYER->getFixed())
        PLAYER->setPosY(PLAYER->getPosY() + 5.0f);

    // 카메라 이동
    if (PLAYER->getCenterX() > WINSIZE_X / 2 && _bf->getX() + 1280 < 2000)
    {
        _bf->setX(_bf->getX() + 4.0f);
        PLAYER->setPosX(PLAYER->getPosX() - 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_ac->getPosX() - 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() - 4);

    }
    if (PLAYER->getLeft() && PLAYER->getCenterX() < WINSIZE_X / 2 + 10 && (_bf->getX() > 0))
    {
        _bf->setX(_bf->getX() - 4.0f);
        PLAYER->setPosX(PLAYER->getPosX() + 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_ac->getPosX() + 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() + 4);
    }
    if (PLAYER->getRect().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        PLAYER->setPosY(PLAYER->getPosY() + 2.0f);
        _bf->setY(_bf->getY() - 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_ac->getPosY() + 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() + 2);
    }
    if (PLAYER->getRect().top > WINSIZE_Y / 2 + 50 && (_bf->getY() + 720 < 938))
    {
        PLAYER->setPosY(PLAYER->getPosY() - 2.0f);
        _bf->setY(_bf->getY() + 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_ac->getPosY() - 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() - 2);
    }

    _bf->rectMove();

    RECT _rt;
    if (PtInRect(&_bf->getLadder(), { (PLAYER->getRect().left + PLAYER->getRect().right) / 2,
        PLAYER->getRect().bottom - 20 }))
    {
        PLAYER->setHold(true);
    }
    else
    {
        PLAYER->setHold(false);
        PLAYER->setFixed(false);
    }

    // 픽셀 충돌
    for (int i = PLAYER->getRect().left; i <= PLAYER->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + i, _bf->getY() + PLAYER->getRect().bottom);

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

    for (int i = PLAYER->getRect().top; i < PLAYER->getRect().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + PLAYER->getRect().left, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
            break;
        } 
    }

    for (int i = PLAYER->getRect().top; i < PLAYER->getRect().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + PLAYER->getRect().right, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);
        
        if ((r == 255 && g == 0 && b == 255))
        {
            PLAYER->setPosX(PLAYER->getPosX() - 4.0f);
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
            if (IntersectRect(&_rt, &PLAYER->getRect(), &_acolyteList[0]->getBoundary(i)))
            {

                if (_acolyteList[0]->isEmpty())
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
        if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &PLAYER->getRect())
            && _acolyteList[0]->getState()[ATTACK_ENEMY] && !PLAYER->getState()[PARRY])
        {
            if (!PLAYER->getState()[HIT] && _acolyteList[0]->canAttack())
            {
                PLAYER->setState(HIT, true);
                PLAYER->setHP(PLAYER->getHP() - 5);
            }
        }
        else if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &PLAYER->getRect()) && PLAYER->getState()[PARRY])
        {
            //if (!PLAYER->getFixed())
            PLAYER->setParry(true);
            //PLAYER->addAction("PARRY_SUCCESS");
        }

        cout << "enemy " << _acolyteList[0]->getHP() << endl;
        if (IntersectRect(&_rt, &_acolyteList[0]->getRect(), &PLAYER->getRect()) && PLAYER->getState()[ATTACK])
        {
            if (!_acolyteList[0]->getState()[HIT_ENEMY])
            {
                _acolyteList[0]->setState(HIT_ENEMY, true);
                //_ac->addAction("Acolyte_hit");
                _acolyteList[0]->setHP(_acolyteList[0]->getHP() - 10);
            }
        } 
        if (_acolyteList[0]->getHP() < 0 && !_acolyteList[0]->getState()[DIE_ENEMY])
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

    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());

    if (_isInven)
    {
        INVENTORY->render(getMemDC());
    }
}
