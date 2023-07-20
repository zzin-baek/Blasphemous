#include "Stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init(void)
{
    _bm = new BossMap;
    _bm->init();

    _pl = new Player;
    _pl->init(88, 484);

    _boss = new Isidora;
    _boss->init();

    _startPos = RectMakeCenter(490, 490, 50, 60);
    _intro = false;
    _cnt = 0;

    return S_OK;
}

void BossStage::release(void)
{
    SAFE_DELETE(_bm);
    SAFE_DELETE(_pl);
}

void BossStage::update(void)
{
    if (!_intro)
    {
        _pl->playerAction();
        _pl->playerMove();


        if (!_pl->getGround())
            _pl->setPosY(_pl->getPosY() + 5.0f);

        if (_pl->getRect().right > WINSIZE_X / 2 && _bm->getPosX() + 1280 < 2400)
        {
            _bm->setPosX(_bm->getPosX() + 4);
            _pl->setPosX(_pl->getPosX() - 4.0f);
            _bm->movdRect(4);
        }
        if (_pl->getLeft() && _pl->getCenterX() < WINSIZE_X / 2 + 10 && (_bm->getPosX() > 0))
        {
            _bm->setPosX(_bm->getPosX() - 4);
            _pl->setPosX(_pl->getPosX() + 4.0f);
            _bm->movdRect(-4);
        }
    }

    if (_intro)
    {
        _cnt++;
        if (_cnt % 2 == 0)
        {
            if (_bm->getPosX() < 650)
            {
                _bm->setPosX(_bm->getPosX() + 8);
                _pl->setPosX(_pl->getPosX() - 8.0f);
                _bm->movdRect(8);
                _boss->setX(_boss->getX() - 8);
            }
        }
        _boss->update();
    }

    RECT _rt;
    if (_pl->getRect().right >= _bm->getRect().right)
    {
        _intro = true;
        _pl->setAction("IDLE");
    }
    for (int i = _pl->getRect().left; i <= _pl->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("BossMap_collision")->getMemDC(),
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
}

void BossStage::render(void)
{
    _bm->render(getMemDC());
    _pl->renderPlayer(getMemDC());
    _pl->renderProfile(getMemDC());

    if (_intro)
        _boss->render(getMemDC());
}
