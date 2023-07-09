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
    if (KEYMANAGER->isStayKeyDown('A'))
    {
        _pl->setLeft(true);
        _pl->setAction("RUNNING");
        _pl->setPosX(_pl->getPosX() - 5.0f);
    }
    if (KEYMANAGER->isStayKeyDown('D'))
    {
        _pl->setLeft(false);
        _pl->setAction("RUNNING");
        _pl->setPosX(_pl->getPosX() + 5.0f);
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _pl->setAction("IDLE");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {

    }

    _cnt++;
    if (_pl->getLeft())
    {
        _pl->setIdxY(1);
        if (_cnt % 5 == 0)
        {
            _pl->setIdxX(_pl->getIdxX() - 1);
            if (_pl->getIdxX() < 0)
            {
                _pl->setIdxX(_pl->getMaxFrameX());
            }
        }
    }
    else
    {
        _pl->setIdxY(0);
        if (_cnt % 5 == 0)
        {
            _pl->setIdxX(_pl->getIdxX() + 1);
            if (_pl->getIdxX() > _pl->getMaxFrameX())
            {
                _pl->setIdxX(0);
            }
        }
    }
}

void BaseMap::render(void)
{
    _bf->render(getMemDC());
    _pl->renderPlayer(getMemDC());
}