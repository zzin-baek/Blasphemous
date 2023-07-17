#include "Stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init(void)
{
    _bm = new BossMap;
    _bm->init();

    _pl = new Player;
    _pl->init();

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
    
}

void BossStage::render(void)
{
    _bm->render(getMemDC());
    _pl->renderPlayer(getMemDC());
}
