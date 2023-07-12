#include "Stdafx.h"
#include "BaseMap.h"

HRESULT BaseMap::init(void)
{
    _pl = new Player;
    _pl->init();

    _bf = new BattleField;
    _bf->init();

    _cnt = 0;
    return S_OK;
}

void BaseMap::release(void)
{
    SAFE_DELETE(_pl);
    SAFE_DELETE(_bf);
}

void BaseMap::update(void)
{
    _pl->playerAction();
    _pl->playerMove();
    if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5.0f);

    if (_pl->getCenterX() > WINSIZE_X / 2 && _bf->getX() + 1280 < 2000)
    {
        _bf->setX(_bf->getX() + 4.0f);
        _pl->setPosX(_pl->getPosX() - 4.0f);

    }
    if (_pl->getLeft() && _pl->getCenterX() < WINSIZE_X / 2 && _bf->getX() > 0)
    {
        _bf->setX(_bf->getX() - 4.0f);
        _pl->setPosX(_pl->getPosX() + 4.0f);
    }
    if (_pl->getRect().top < WINSIZE_Y / 2 && _bf->getY() > 0)
    {
        _pl->setPosY(_pl->getPosY() + 2.0f);
        _bf->setY(_bf->getY() - 2.0f);
    }
    if (_pl->getRect().top > WINSIZE_Y / 2 + 50 && (_bf->getY() + 720 < 938))
    {
        _pl->setPosY(_pl->getPosY() - 2.0f);
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

    for (int i = _pl->getRect().left; i <= _pl->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("bg_collision")->getMemDC(), 
            _bf->getX() + i, _bf->getY() + _pl->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            //_pl->setPosY(_pl->getPosY() - 5.0f);
            _pl->setGround(true);
            break;
        }
        _pl->setGround(false);
    }
}

void BaseMap::render(void)
{
    _bf->render(getMemDC());
    _pl->renderPlayer(getMemDC());

    cout << "walk " << _pl->getState()[WALK] << endl;
    cout << "jump " << _pl->getState()[JUMP] << endl;
    cout << "crouch " << _pl->getState()[CROUCH] << endl;
    cout << "dodge " << _pl->getState()[DODGE] << endl;
    cout << _pl->getGround() << endl;
}