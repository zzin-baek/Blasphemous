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
    /*if (KEYMANAGER->isStayKeyDown('A'))
    {
        _pl->setLeft(true);
        _pl->setState(WALK, true);
        if (!_pl->getState()[JUMP])
            _pl->setAction("RUNNING");
        _pl->setPosX(_pl->getPosX() - 5.0f);
    }
    if (KEYMANAGER->isStayKeyDown('D'))
    {
        _pl->setLeft(false);
        _pl->setState(WALK, true);
        if (!_pl->getState()[JUMP])
            _pl->setAction("RUNNING");
        _pl->setPosX(_pl->getPosX() + 5.0f);
    }
    if (KEYMANAGER->isStayKeyDown('S'))
    {
        _pl->setState(CROUCH, true);
        if (_pl->isIdle())
            _pl->setAction("CROUCH_DOWN");
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _pl->resetState();
        _pl->setAction("IDLE");
    }

    if (KEYMANAGER->isOnceKeyUp('S'))
    {
        _pl->setAction("CROUCH_UP");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_pl->getState()[WALK] || _pl->getState()[DODGE])
        {
            _pl->setState(JUMP, true);
            _pl->setAction("JUMP_FORWARD");
        }
        else if (_pl->isIdle())
        {
            _pl->setState(JUMP, true);
            _pl->setAction("JUMP");
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
    {
        _pl->setState(DODGE, true);
        _pl->setAction("DODGE");
    }
    if (KEYMANAGER->isOnceKeyDown('K'))
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
    */

}

void BaseMap::render(void)
{
    _bf->render(getMemDC());
    _pl->renderPlayer(getMemDC());

    cout << "walk " << _pl->getState()[WALK] << endl;
    cout << "jump " << _pl->getState()[JUMP] << endl;
    cout << "crouch " << _pl->getState()[CROUCH] << endl;
    cout << "dodge " << _pl->getState()[DODGE] << endl;
    cout << _pl->getLeft() << endl;
}