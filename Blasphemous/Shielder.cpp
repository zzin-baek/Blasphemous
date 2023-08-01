#include "Stdafx.h"
#include "Shielder.h"

HRESULT Shielder::init(void)
{
    IMAGEMANAGER->addFrameImage("Shielder_idle", "Resources/Image/Enemy/shieldandsword_idle.bmp",
        744 * 2, 130 * 2, 12, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Shielder_walk", "Resources/Image/Enemy/shieldandsword_walking_anim.bmp",
        682 * 2, 128 * 2, 11, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Shielder_attack", "Resources/Image/Enemy/shieldMaiden_attack.bmp",
        1200 * 2, 152 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Shielder_death", "Resources/Image/Enemy/shieldandsword_death.bmp",
        4180 * 2, 204 * 2, 38, 2, true, MAGENTA);

    _cnt = 0;
    _idx = { 0, 0 };
    _isLeft = _die = _hit = _isAttack = false;

    _shState.reset();
    _hp = 50;

    setState(IDLE_ENEMY, true);
    wsprintf(_strAction, "Shielder_walk");

    initSync();

    return S_OK;
}

HRESULT Shielder::init(float locX, float locY)
{
    _shielderPos = { locX, locY };

    return S_OK;
}

void Shielder::initSync(void)
{
    _sync.insert({ "Shielder_idle", {5, {0, 0}, {0, 0}} });
    _sync.insert({ "Shielder_walk", {8, {0, 0}, {0, 0}} });
    _sync.insert({ "Shielder_attack", {5, {0, 0}, {0, 0}} });
    _sync.insert({ "Shielder_death", {5, {0, 0}, {0, 0}} });
}

void Shielder::move(void)
{
    if (_isLeft && _shState[IDLE_ENEMY])
    {
        _shielderPos.x -= 1;
    }
    else if (!_isLeft && _shState[IDLE_ENEMY])
    {
        _shielderPos.x += 1;
    }

    _cnt++;
    if (isEmpty())
    {
        if (_isLeft)
        {
            _idx.y = 1;
            IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx.y);
            if (_cnt % _sync[_strAction].timing == 0)
            {
                _idx.x--;
                if (_idx.x < 1)
                {
                    _idx.x = getMaxFrame();
                }
                IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx.x);
            }
        }
        else
        {
            _idx.y = 0;
            IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx.y);
            if (_cnt % _sync[_strAction].timing == 0)
            {
                _idx.x++;
                if (_idx.x > getMaxFrame())
                {
                    _idx.x = 0;
                }
                IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx.x);
            }
        }
    }
    else
    {
        if (_isLeft)
        {
            _idx.y = 1;
            IMAGEMANAGER->findImage(_shList.front())->setFrameY(_idx.y);
            if (_cnt % _sync[_shList.front()].timing == 0)
            {
                _idx.x--;
                if (_idx.x < 1)
                {
                    //if (!strcmp(_shList.front(), "Acolyte_death") && getState()[DIE_ENEMY])
                    //    _die = true;//setState(DIE_ENEMY, true);                 
                    _shList.pop_front();
                    if (!_shList.empty())
                    {
                        _idx.x = IMAGEMANAGER->findImage(_shList.front())->getMaxFrameX();
                        setAction(_shList.front());
                        _shState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])
                            _die = true;

                        _shState.reset();
                        _hit = false;

                        setState(IDLE_ENEMY, true);
                        setAction("Acolyte_walk");

                        if (_die) setState(DIE_ENEMY, true);
                    }
                }
                if (!_shList.empty())
                    IMAGEMANAGER->findImage(_shList.front())->setFrameX(_idx.x);
            }
        }
        else
        {
            _idx.y = 0;
            IMAGEMANAGER->findImage(_shList.front())->setFrameY(_idx.y);
            if (_cnt % _sync[_shList.front()].timing == 0)
            {
                _idx.x++;
                if (_idx.x > IMAGEMANAGER->findImage(_shList.front())->getMaxFrameX())
                {
                    //if (!strcmp(_shList.front(), "Acolyte_death") && getState()[DIE_ENEMY])
                    //    _die = true;//setState(DIE_ENEMY, true);
                    _shList.pop_front();
                    if (!_shList.empty())
                    {
                        _idx.x = 0;
                        setAction(_shList.front());
                        _shState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])
                            _die = true;
                        _shState.reset();
                        _hit = false;

                        setState(IDLE_ENEMY, true);
                        setAction("Shielder_walk");

                        if (_die) setState(DIE_ENEMY, true);
                    }
                }
                if (!_shList.empty())
                    IMAGEMANAGER->findImage(_shList.front())->setFrameX(_idx.x);
            }
        }
    }
}

void Shielder::render(HDC hdc)
{
    if (_shList.empty())
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_strAction].leftMove.x,
                _shielderPos.y + _sync[_strAction].leftMove.y, IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
        }
        else
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_strAction].rightMove.x,
                _shielderPos.y + _sync[_strAction].rightMove.y, IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
        }
    }
    else
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_shList.front(), hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_shList.front())->getFrameWidth() / 2 + _sync[_shList.front()].leftMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_shList.front())->getFrameHeight() / 2 + _sync[_shList.front()].leftMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_shList.front()].leftMove.x,
                _shielderPos.y + _sync[_shList.front()].leftMove.y, IMAGEMANAGER->findImage(_shList.front())->getFrameWidth(),
                IMAGEMANAGER->findImage(_shList.front())->getFrameHeight());
        }
        else
        {
            IMAGEMANAGER->frameRender(_shList.front(), hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_shList.front())->getFrameWidth() / 2 + _sync[_shList.front()].rightMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_shList.front())->getFrameHeight() / 2 + _sync[_shList.front()].rightMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_shList.front()].rightMove.x,
                _shielderPos.y + _sync[_shList.front()].rightMove.y, IMAGEMANAGER->findImage(_shList.front())->getFrameWidth(),
                IMAGEMANAGER->findImage(_shList.front())->getFrameHeight());
        }
    }

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _attackBoundary);
        _stprintf_s(_loc, "x: %.2f y: %.2f", _shielderPos.x, _shielderPos.y);
        TextOut(hdc, _shielderPos.x, _shielderPos.y, _loc, strlen(_loc));
        TextOut(hdc, _shielderPos.x, _shielderPos.y + 20, _strAction, strlen(_strAction));

        myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _shielder);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
