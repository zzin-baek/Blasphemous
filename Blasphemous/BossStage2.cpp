#include "Stdafx.h"
#include "BossStage2.h"

HRESULT BossStage2::init(void)
{
	_bm = new BossMap2;
	_bm->init();

	_boss = new Pietat;
	_boss->init();

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

    if (PLAYER->getHitBox().right > WINSIZE_X / 2 && _bm->getPosX() + 1280 < 4000)
    {
        _bm->setPosX(_bm->getPosX() + 4);
        PLAYER->setPosX(PLAYER->getPosX() - 4.0f);
    }
    if (PLAYER->getLeft() && PLAYER->getHitBox().left < WINSIZE_X / 2 + 10 && (_bm->getPosX() > 0))
    {
        _bm->setPosX(_bm->getPosX() - 4);
        PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
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
}

void BossStage2::render(void)
{
    _bm->render(getMemDC());

    _boss->render(getMemDC());

    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());

    _bm->renderColumn(getMemDC());
}
