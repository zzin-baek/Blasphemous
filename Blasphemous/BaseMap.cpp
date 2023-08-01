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

    _sh = new Shielder;
    _sh->init();

    _acolyteList.push_back(_ac);
    // stoner 2마리 생성
    for (int i = 0; i < 2; i++)
    {
        _st = new Stoner;
        _st->init();

        _stonerList.push_back(_st);
    }
    _shielderList.push_back(_sh);

    _item = new Item;
    _item->init(1050, 135);

    _itemList.push_back(_item);

    // stoner위치 초기화
    _stonerList[0]->init(WINSIZE_X + 50, WINSIZE_Y / 2 - 45);
    _stonerList[1]->init(2626, WINSIZE_Y / 2 - 138);

    _shielderList[0]->init(100, 410);

    _nextStage = _preStage = _cnt = _term = 0;
    _isInven = false;

    return S_OK;
}

void BaseMap::release(void)
{
    SAFE_DELETE(_bf);
    SAFE_DELETE(_ac);
    SAFE_DELETE(_st);
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
        if (!_stonerList.empty())
        {
            for (int i = 0; i < _stonerList.size(); i++)
                _stonerList[i]->move();
        }
        if (!_shielderList.empty())
            _shielderList[0]->move();
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

    // 스테이지 이동
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
    if (PLAYER->getHitBox().right > WINSIZE_X / 2 && _bf->getX() + 1280 < 3760) //2000
    {
        _bf->setX(_bf->getX() + 4.0f);
        PLAYER->setPosX(PLAYER->getPosX() - 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_acolyteList[0]->getPosX() - 4);
        if (!_stonerList.empty())
        {
            for (int i = 0; i < _stonerList.size(); i++)
            {
                _stonerList[i]->setPosX(_stonerList[i]->getPosX() - 4);
                _stonerList[i]->setRockPos(-4, 0);
            }
        }
        if (!_shielderList.empty())
            _shielderList[0]->setPosX(_shielderList[0]->getPosX() - 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() - 4);

    }
    if (PLAYER->getLeft() && PLAYER->getHitBox().left < WINSIZE_X / 2 && (_bf->getX() > 0))
    {
        _bf->setX(_bf->getX() - 4.0f);
        PLAYER->setPosX(PLAYER->getPosX() + 4.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosX(_acolyteList[0]->getPosX() + 4);
        if (!_stonerList.empty())
        {
            for (int i = 0; i < _stonerList.size(); i++)
            {
                _stonerList[i]->setPosX(_stonerList[i]->getPosX() + 4);
                _stonerList[i]->setRockPos(4, 0);
            }
        }
        if (!_shielderList.empty())
            _shielderList[0]->setPosX(_shielderList[0]->getPosX() + 4);
        if (!_itemList.empty())
            _itemList[0]->setPosX(_item->getPosX() + 4);
    }
    if (PLAYER->getHitBox().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        PLAYER->setPosY(PLAYER->getPosY() + 2.0f);
        _bf->setY(_bf->getY() - 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_acolyteList[0]->getPosY() + 2);
        if (!_stonerList.empty())
        {
            for (int i = 0; i < _stonerList.size(); i++)
            {
                _stonerList[i]->setPosY(_stonerList[i]->getPosY() + 2);
                _stonerList[i]->setRockPos(0, 2);
            }
        }
        if (!_shielderList.empty())
            _shielderList[0]->setPosY(_shielderList[0]->getPosY() + 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() + 2);
    }
    if (PLAYER->getHitBox().top > WINSIZE_Y / 2 + 50 && (_bf->getY() + 720 < 940)) //938
    {
        PLAYER->setPosY(PLAYER->getPosY() - 2.0f);
        _bf->setY(_bf->getY() + 2.0f);

        if (!_acolyteList.empty())
            _acolyteList[0]->setPosY(_acolyteList[0]->getPosY() - 2);
        if (!_stonerList.empty())
        {
            for (int i = 0; i < _stonerList.size(); i++)
            {
                _stonerList[i]->setPosY(_stonerList[i]->getPosY() - 2);
                _stonerList[i]->setRockPos(0, -2);
            }
        }
        if (!_shielderList.empty())
            _shielderList[0]->setPosY(_shielderList[0]->getPosY() - 2);
        if (!_itemList.empty())
            _itemList[0]->setPosY(_item->getPosY() - 2);
    }

    _bf->rectMove();

    if (!_stonerList.empty())
    {
        for (int i = 0; i < _stonerList.size(); i++)
        {
            RECT _rt;
            if (IntersectRect(&_rt, &PLAYER->getHitBox(), &_stonerList[i]->getBoundary()))
            {
                if (!_once[i])
                {
                    _stonerList[i]->setRising(true);
                    _stonerList[i]->addAction("Stoner_rising");
                    _once.set(i, true);
                }
                else
                {
                    _stonerList[i]->setState(ATTACK_ENEMY, true);
                }

            }
        }
    }
    RECT _rt;
    if (PtInRect(&_bf->getLadder(), { (PLAYER->getHitBox().left + PLAYER->getHitBox().right) / 2,
        PLAYER->getHitBox().bottom - 20 }))
    {
        PLAYER->setHold(true);
    }
    else
    {
        PLAYER->setHold(false);
        PLAYER->setFixed(false);
    }

    // 픽셀 충돌
    for (int i = PLAYER->getHitBox().left; i <= PLAYER->getHitBox().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + i, _bf->getY() + PLAYER->getHitBox().bottom);

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

    for (int i = PLAYER->getHitBox().top; i < PLAYER->getHitBox().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + PLAYER->getHitBox().left, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
            break;
        } 
    }

    for (int i = PLAYER->getHitBox().top; i < PLAYER->getHitBox().bottom - 40; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + PLAYER->getHitBox().right, _bf->getY() + i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);
        
        if ((r == 255 && g == 0 && b == 255))
        {
            PLAYER->setPosX(PLAYER->getPosX() - 4.0f);
            break;
        }
    }

    if (!_acolyteList.empty()) // acolyte전투
    {
        // acolyte 픽셀충돌
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _acolyteList[0]->getPosX() + 80, _bf->getY() + _acolyteList[0]->getPosY());

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            if (!_acolyteList[0]->getState()[ATTACK_ENEMY])
                _acolyteList[0]->setLeft(true);
            else if (_acolyteList[0]->getState()[ATTACK_ENEMY])
            {
                // 멈추기
                _acolyteList[0]->setState(ATTACK_ENEMY, false);
                _acolyteList[0]->addAction("Acolyte_idle");
            }
        }

        color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _acolyteList[0]->getPosX() + 30, _bf->getY() + _acolyteList[0]->getPosY() - 50);

        r = GetRValue(color);
        g = GetGValue(color);
        b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            if (!_acolyteList[0]->getState()[ATTACK_ENEMY])
                _acolyteList[0]->setLeft(false);
            else if (_acolyteList[0]->getState()[ATTACK_ENEMY])
            {
                // 멈추기
                _acolyteList[0]->setState(ATTACK_ENEMY, false);
                _acolyteList[0]->addAction("Acolyte_idle");
            }
            else
            {
                _acolyteList[0]->setPosX(_acolyteList[0]->getRect().left);
                _acolyteList[0]->setPosY(_acolyteList[0]->getRect().bottom);
            }
        }

        // 전투
        for (int i = 0; i < 2; i++)
        {
            if (IntersectRect(&_rt, &PLAYER->getHitBox(), &_acolyteList[0]->getBoundary(i)))
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
        if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &PLAYER->getHitBox())
            && _acolyteList[0]->getState()[ATTACK_ENEMY] && !PLAYER->getState()[PARRY])
        {
            if (!PLAYER->getState()[HIT] && !PLAYER->getHit() && _acolyteList[0]->canAttack())
            {
                //PLAYER->setState(HIT, true);
                PLAYER->setHit(true);
                PLAYER->setHP(PLAYER->getHP() - 5);
            }
        }
        else if (IntersectRect(&_rt, &_acolyteList[0]->getAttack(), &PLAYER->getHitBox()) && PLAYER->getState()[PARRY])
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
        if (_acolyteList[0]->getHP() <= 0 && _acolyteList[0]->getDie())
        {
            _acolyteList.pop_back();
        }
    }

    if (!_stonerList.empty())
    {
        for (int i = 0; i < _stonerList.size(); i++)
        {
            _stonerList[i]->rockCollision();

            cout << "돌"<<_stonerList[i]->getHP() << endl;
            if (IntersectRect(&_rt, &_stonerList[i]->getRect(), &PLAYER->getRect()) && PLAYER->getState()[ATTACK])
            {
                if (!_stonerList[i]->getState()[HIT_ENEMY])
                {
                    _stonerList[i]->setState(HIT_ENEMY, true);
                    _stonerList[i]->setHP(_stonerList[i]->getHP() - 10);
                }
            }
            if (_stonerList[i]->getHP() <= 0 && _stonerList[i]->getDie())
            {
                _stonerList.erase(_stonerList.begin() + i);
            }
        }
    }

    if (!_shielderList.empty())
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _shielderList[0]->getRect().right, _bf->getY() + _shielderList[0]->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            _shielderList[0]->setLeft(!_shielderList[0]->getLeft());
        }

        color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
            _bf->getX() + _acolyteList[0]->getPosX() + 30, _bf->getY() + _acolyteList[0]->getPosY() - 50);

        r = GetRValue(color);
        g = GetGValue(color);
        b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            if (!_acolyteList[0]->getState()[ATTACK_ENEMY])
                _acolyteList[0]->setLeft(false);          
            else
            {
                _acolyteList[0]->setPosX((_acolyteList[0]->getRect().left + _acolyteList[0]->getRect().right) / 2);
                _acolyteList[0]->setPosY((_acolyteList[0]->getRect().bottom + _acolyteList[0]->getRect().top) / 2);
            }
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
    if (!_stonerList.empty())
    {
        for (int i = 0; i < _stonerList.size(); i++)
        {
            _stonerList[i]->render(getMemDC());
        }
    }
    if (!_shielderList.empty())
        _shielderList[0]->render(getMemDC());

    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());

    _bf->renderDoor(getMemDC());

    if (_isInven)
    {
        INVENTORY->render(getMemDC());
    }
}
