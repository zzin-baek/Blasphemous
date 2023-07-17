#include "Stdafx.h"
#include "BaseMap.h"

HRESULT BaseMap::init(void)
{
    _pl = new Player;
    _pl->init();

    _bf = new BattleField;
    _bf->init();

    _ac = new Acolyte;
    _ac->init();

    _nextStage = 0;
    _cnt = 0;
    return S_OK;
}

void BaseMap::release(void)
{
    SAFE_DELETE(_pl);
    SAFE_DELETE(_bf);
    SAFE_DELETE(_ac);
}

void BaseMap::update(void)
{
    _pl->playerAction();
    _pl->playerMove();
    _ac->move();

    if (_pl->getRect().left >= WINSIZE_X)
        _nextStage = 1;

    // 중력
    if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5.0f);

    // 카메라 이동
    if (_pl->getCenterX() > WINSIZE_X / 2 && _bf->getX() + 1280 < 2000)
    {
        _bf->setX(_bf->getX() + 4.0f);
        _ac->setPosX(_ac->getPosX() - 4);
        _pl->setPosX(_pl->getPosX() - 4.0f);

    }
    if (_pl->getLeft() && _pl->getCenterX() < WINSIZE_X / 2 + 10 && _bf->getX() > 0)
    {
        _bf->setX(_bf->getX() - 4.0f);
        _ac->setPosX(_ac->getPosX() + 4);
        _pl->setPosX(_pl->getPosX() + 4.0f);
    }
    if (_pl->getRect().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        _pl->setPosY(_pl->getPosY() + 2.0f);
        _ac->setPosY(_ac->getPosY() + 2);
        _bf->setY(_bf->getY() - 2.0f);
    }
    if (_pl->getRect().top > WINSIZE_Y / 2 + 50 && (_bf->getY() + 720 < 938))
    {
        _pl->setPosY(_pl->getPosY() - 2.0f);
        _ac->setPosY(_ac->getPosY() - 2);
        _bf->setY(_bf->getY() + 2.0f);
    }

    /*if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5);

    if (_pl->getCenterX() > WINSIZE_X / 2 && _bf->getX() + 680 < 1280)
    {
        _bf->setX(_bf->getX() + 3);
        _pl->setPosX(_pl->getPosX() - 3);
    }
    if (_pl->getLeft() && _pl->getCenterX() < WINSIZE_X / 2 && _bf->getX() > 0)
    {
        _bf->setX(_bf->getX() - 3);
        _pl->setPosX(_pl->getPosX() + 3);
    }
    if (_pl->getRect().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        _bf->setY(_bf->getY() - 2);
    }
    if (_pl->getRect().top > WINSIZE_Y / 2 && (_bf->getY() + 380 < 600))
    {
        _bf->setY(_bf->getY() + 2);
    }*/

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
            break;
        }
        _pl->setGround(false);
    }
    for (int i = _pl->getRect().top; i < _pl->getRect().bottom - 10; i++)
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

    for (int i = _pl->getRect().top; i < _pl->getRect().bottom - 10; i++)
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

    COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
        _bf->getX() + _ac->getPosX() + 80, _bf->getY() + _ac->getPosY());

    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    if (!(r == 255 && g == 0 && b == 255))
    {
        _ac->setLeft(true);
    }

    color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(),
        _bf->getX() + _ac->getPosX() + 30, _bf->getY() + _ac->getPosY() - 50);

    r = GetRValue(color);
    g = GetGValue(color);
    b = GetBValue(color);

    if ((r == 255 && g == 0 && b == 255))
    {
        _ac->setLeft(false);
    }

    // 전투
    RECT _rt;
    for (int i = 0; i < 2; i++)
    {
        if (IntersectRect(&_rt, &_pl->getRect(), &_ac->getBoundary(i)))
        {

            if (_ac->isEmpty())
            {
                _ac->setAction("Acolyte_attack");
                _ac->setState(IDLE_ENEMY, false);
                _ac->setState(ATTACK_ENEMY, true);
                _ac->addAction("Acolyte_attack");

                if (i == 0)
                {
                    _ac->setLeft(true);
                    _ac->setX(_ac->getMaxFrame());
                }
                else
                {
                    _ac->setLeft(false);
                    _ac->setX(0);

                }
            }
        }
    }
    if (IntersectRect(&_rt, &_ac->getAttack(), &_pl->getRect()) && !_pl->getState()[PARRY])
    {
        if (!_pl->getState()[HIT])
        {
            _pl->setState(HIT, true);
            _pl->setHP(_pl->getHP() - 5);
        }
    }

}

void BaseMap::render(void)
{
    _bf->render(getMemDC());
    _pl->renderPlayer(getMemDC());
    _ac->render(getMemDC());
    _pl->renderProfile(getMemDC());

}