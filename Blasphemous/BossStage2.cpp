#include "Stdafx.h"
#include "BossStage2.h"

HRESULT BossStage2::init(void)
{
	_bm = new BossMap2;
	_bm->init();

	_boss = new Pietat;
	_boss->init();

    _cnt = 0;
    _once = false;

	return S_OK;
}

void BossStage2::release(void)
{
	SAFE_DELETE(_bm);
	SAFE_DELETE(_boss);
}

void BossStage2::update(void)
{

    PLAYER->playerAction();
    PLAYER->playerMove();

    if (!PLAYER->getFixed())
        PLAYER->setPosY(PLAYER->getPosY() + 5.0f);

    //if (PLAYER->getHitBox().left <= 0)
    //    PLAYER->setPosX(PLAYER->getPosX() + 4.0f);

    if (!_boss->getIntro())
    {
        PLAYER->setPress(true);

        if (PLAYER->getHitBox().right > WINSIZE_X / 2 && _bm->getPosX() + 1280 < 3200)
        {
            _bm->setPosX(_bm->getPosX() + 4);
            _bm->moveRect(4);
            PLAYER->setPosX(PLAYER->getPosX() - 4.0f);

            _boss->setX(_boss->getX() - 4.0f);
            _boss->setThornPos(-4);
        }
        if (PLAYER->getLeft() && PLAYER->getHitBox().left < WINSIZE_X / 2 + 10 && (_bm->getPosX() > 100))
        {
            _bm->setPosX(_bm->getPosX() - 4);
            _bm->moveRect(-4);
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);

            _boss->setX(_boss->getX() + 4.0f);
            _boss->setThornPos(4);
        }
    }

    RECT _rt;
    if (PLAYER->getCenterX() <= _bm->getRect().right && !_once)
    {
        _boss->setIntro(true);
        _once = true;
    }

    if (_boss->getIntro())
    {
        PLAYER->setPress(false);
        _cnt++;
        PLAYER->setPress(false);
        if (_cnt % 2 == 0)
        {
            if (_bm->getPosX() > 700)
            {
                _bm->setPosX(_bm->getPosX() - 7);
                PLAYER->setPosX(PLAYER->getPosX() + 7.0f);
                _bm->moveRect(-7);
                _boss->setX(_boss->getX() + 7);
            }
        }
    }

    for (int i = PLAYER->getHitBox().left; i <= PLAYER->getHitBox().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("Piedad_map_collision")->getMemDC(),
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

    _boss->update();
}

void BossStage2::render(void)
{
    _bm->render(getMemDC());

    _boss->render(getMemDC());

    PLAYER->renderPlayer(getMemDC());

    _bm->renderColumn(getMemDC());

    if (_once)
        _boss->renderHP(getMemDC());
    PLAYER->renderProfile(getMemDC());
}
