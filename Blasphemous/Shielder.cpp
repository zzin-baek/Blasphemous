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
    IMAGEMANAGER->addFrameImage("Shielder_parry", "Resources/Image/Enemy/shieldMaiden_parryReaction.bmp",
        1495 * 2, 152 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Shielder_parryToIdle", "Resources/Image/Enemy/shieldMaiden_parryReactionToIdle.bmp",
        356 * 2, 128 * 2, 4, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Shielder_death", "Resources/Image/Enemy/shieldandsword_death.bmp",
        4180 * 2, 204 * 2, 38, 2, true, MAGENTA);

    _cnt = 0;
    _idx = { 0, 0 };
    _isLeft = true;
    _die = _hit = _isAttack = false;

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
    _sync.insert({ "Shielder_attack", {5, {0, -12}, {-8, -12}} });
    _sync.insert({ "Shielder_parry", {8, {0, -12}, {0, -12}} });
    _sync.insert({ "Shielder_parryToIdle", {8, {0, 0}, {0, 0}} });
    _sync.insert({ "Shielder_death", {7, {-20, -30}, {-20, -30}} });
}

void Shielder::move(void)
{
    _attackBoundary[0] = RectMake(_shielder.left - 80, _shielder.top + 20, 80, 100);
    _attackBoundary[1] = RectMake(_shielder.right, _shielder.top + 20, 80, 100);

    if (_isLeft)
        _attack = RectMake(_shielder.left - 75, _shielder.top + 30, 70, 80);
    else
        _attack = RectMake(_shielder.right + 5, _shielder.top + 30, 70, 80);


    if (_isLeft && _shState[IDLE_ENEMY])
    {
        _shielderPos.x -= 1;
    }
    else if (!_isLeft && _shState[IDLE_ENEMY])
    {
        _shielderPos.x += 1;
    }

    if (_shState[HIT_ENEMY] && !_hit)
    {
        _shList.clear();
        //_acState.reset();
        setState(ATTACK_ENEMY, false);
        _hit = true;
    }

    if (_hp <= 0 && !getState()[DIE_ENEMY])
    {
        setState(IDLE_ENEMY, false);
        setState(DIE_ENEMY, true);
        //_die = true;

        _shList.clear();
        _shList.push_back("Shielder_death");

        if (_isLeft)
            _idx.x = IMAGEMANAGER->findImage("Shielder_death")->getMaxFrameX();
        else
            _idx.x = 0;
    }

    if(!isEmpty())
        if (!strcmp(_shList.front(), "Shielder_parry"))
            _isAttack = false;

    attack();
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
                        //_shState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])
                            _die = true;

                        _hit = false;
                        _shState.reset();

                        setState(IDLE_ENEMY, true);
                        setAction("Shielder_walk");

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
                        //_shState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])
                            _die = true;

                        _hit = false;
                        _shState.reset();

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

void Shielder::attack(void)
{
    if (_shState[ATTACK_ENEMY] && !strcmp(_strAction, "Shielder_attack"))
    {
        if (_isLeft)
        {
            if (_idx.x < (getMaxFrame() - 4) && _idx.x >(getMaxFrame() - 7))
                _isAttack = true;            
            else _isAttack = false;
        }
        else
        {
            if (_idx.x > 4 && _idx.x < 7)            
                _isAttack = true;            
            else _isAttack = false;
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
                _shielderPos.y + _sync[_strAction].leftMove.y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 - 62,
                100, 120);
        }
        else
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_strAction].rightMove.x,
                _shielderPos.y + _sync[_strAction].rightMove.y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 - 62,
                100, 120);
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
                _shielderPos.y + _sync[_shList.front()].leftMove.y + IMAGEMANAGER->findImage(_shList.front())->getFrameHeight() / 2 - 62,
                100, 120);
        }
        else
        {
            IMAGEMANAGER->frameRender(_shList.front(), hdc,
                _shielderPos.x - IMAGEMANAGER->findImage(_shList.front())->getFrameWidth() / 2 + _sync[_shList.front()].rightMove.x,
                _shielderPos.y - IMAGEMANAGER->findImage(_shList.front())->getFrameHeight() / 2 + _sync[_shList.front()].rightMove.y,
                _idx.x, _idx.y);

            _shielder = RectMakeCenter(_shielderPos.x + _sync[_shList.front()].rightMove.x,
                _shielderPos.y + _sync[_shList.front()].rightMove.y + IMAGEMANAGER->findImage(_shList.front())->getFrameHeight() / 2 - 62,
                100, 120);
        }
    }

    IMAGEMANAGER->render("ENEMY_HP_BAR", hdc, _shielderPos.x - 30, _shielderPos.y - 70);
    IMAGEMANAGER->render("ENEMY_HP", hdc, _shielderPos.x - 30 + 2, _shielderPos.y - 68, 0, 0,
        IMAGEMANAGER->findImage("ENEMY_HP")->getWidth() * _hp / 50, IMAGEMANAGER->findImage("ENEMY_HP")->getHeight());


    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        if (_isAttack)
        {
            DrawRectMake(hdc, _attack);
        }

        _stprintf_s(_loc, "x: %.2f y: %.2f", _shielderPos.x, _shielderPos.y);
        TextOut(hdc, _shielderPos.x, _shielderPos.y, _loc, strlen(_loc));
        TextOut(hdc, _shielderPos.x, _shielderPos.y + 20, _strAction, strlen(_strAction));

        myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _shielder);
        DrawRectMake(hdc, _attackBoundary[0]);
        DrawRectMake(hdc, _attackBoundary[1]);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
