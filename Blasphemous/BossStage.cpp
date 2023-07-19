#include "Stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init(void)
{
    _bm = new BossMap;
    _bm->init();

    _pl = new Player;
    _pl->init(88, 484);

    return S_OK;
}

void BossStage::release(void)
{
    SAFE_DELETE(_bm);
    SAFE_DELETE(_pl);
}

void BossStage::update(void)
{
    _pl->playerAction();
    _pl->playerMove();
    
    if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5.0f);

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
}
