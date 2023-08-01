#include "Stdafx.h"
#include "Acolyte.h"

HRESULT Acolyte::init(void)
{
    IMAGEMANAGER->addFrameImage("Acolyte_idle", "Resources/Image/Enemy/acolite_idle_anim.bmp",
        585 * 2, 248 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Acolyte_walk", "Resources/Image/Enemy/acolite_walking_anim.bmp",
        705 * 2, 260 * 2, 15, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Acolyte_attack", "Resources/Image/Enemy/acolyte_attack_anim.bmp",
        4899 * 2, 258 * 2, 23, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Acolyte_hit", "Resources/Image/Enemy/acolyte_get_hit_anim.bmp",
        1176 * 2, 236 * 2, 12, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Acolyte_parry", "Resources/Image/Enemy/acolyte_parry_reaction_anim.bmp",
        1963 * 2, 224 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Acolyte_death", "Resources/Image/Enemy/acolyte_death_anim.bmp",
        3960 * 2, 266 * 2, 22, 2, true, MAGENTA);

    _acolytePos = { WINSIZE_X / 2 + 500, WINSIZE_Y / 2 + 330 };
    _isLeft = _canAttack = _hit = _die = false;
    _cnt = _idx_x = _idx_y = 0;

    _acState.reset();
    _hp = 50;

    setState(IDLE_ENEMY, true);
    wsprintf(_strAction, "Acolyte_walk");

    initSync();

    return S_OK;
}

void Acolyte::initSync(void)
{
    _sync.insert({ "Acolyte_idle", { 4, {-5, 0}, {10, 0} } });
    _sync.insert({ "Acolyte_walk", { 5, {0, 0}, {0, 0} } });
    _sync.insert({ "Acolyte_attack", { 7, {-180, 20}, {-150, 20} } });
    _sync.insert({ "Acolyte_hit", { 7, {10, 0}, {-120, 0} } });
    _sync.insert({ "Acolyte_parry", { 7, {0, 0}, {0, 0} } });
    _sync.insert({ "Acolyte_death", { 7, {-150, 0}, {-130, 0} } });
}


void Acolyte::move(void)
{
    if (_isLeft && _acState[IDLE_ENEMY])
    {
        _acolytePos.x -= 1;
    }
    else if (!_isLeft && _acState[IDLE_ENEMY])
    {
        _acolytePos.x += 1;
    }


    if (_acState[ATTACK_ENEMY])
    {
        if (_isLeft)
        {
            _attack = RectMake(_attackBoundary[0].left + 20, _attackBoundary[0].top + 15, 90, 55);
        }
        else
        {
            _attack = RectMake(_attackBoundary[1].right - 120, _attackBoundary[1].top + 15, 90, 55);
        }
    }

    if (_acState[HIT_ENEMY] && !_hit)
    {
        _acList.clear();
        _acState.reset();
        _hit = true;
        _acList.push_back("Acolyte_hit");

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("Acolyte_hit")->getMaxFrameX();
        else
            _idx_x = 0;
    }

    if (_hp < 0 && !getState()[DIE_ENEMY])
    {
        setState(IDLE_ENEMY, false);
        setState(DIE_ENEMY, true);
        //_die = true;

        _acList.clear();
        _acList.push_back("Acolyte_death");

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("Acolyte_death")->getMaxFrameX();
        else
            _idx_x = 0;
    }

    _cnt++;
    if (isEmpty())
    {
        if (_isLeft)
        {
            _idx_y = 1;
            IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
            if (_cnt % _sync[_strAction].timing == 0)
            {
                _idx_x--;
                if (_idx_x < 1)
                {
                    _idx_x = getMaxFrame();
                }
                IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx_x);
            }
        }
        else
        {
            _idx_y = 0;
            IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
            if (_cnt % _sync[_strAction].timing == 0)
            {
                _idx_x++;
                if (_idx_x > getMaxFrame())
                {
                    _idx_x = 0;
                }
                IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx_x);
            }
        }
    }
    else
    {
        if (_isLeft)
        {
            _idx_y = 1;
            IMAGEMANAGER->findImage(_acList.front())->setFrameY(_idx_y);
            if (_cnt % _sync[_acList.front()].timing == 0)
            {
                _idx_x--;
                if (_idx_x < 1)
                {
                    //if (!strcmp(_acList.front(), "Acolyte_death") && getState()[DIE_ENEMY])
                    //    _die = true;//setState(DIE_ENEMY, true);                 
                    _acList.pop_front();
                    if (!_acList.empty())
                    {
                        _idx_x = IMAGEMANAGER->findImage(_acList.front())->getMaxFrameX();
                        setAction(_acList.front());
                        _acState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])                      
                            _die = true;

                        _acState.reset();
                        _hit = false;
                        
                        setState(IDLE_ENEMY, true);
                        setAction("Acolyte_walk");

                        if (_die) setState(DIE_ENEMY, true);
                    }
                }
                if (!_acList.empty())
                    IMAGEMANAGER->findImage(_acList.front())->setFrameX(_idx_x);
            }
        }
        else
        {
            _idx_y = 0;
            IMAGEMANAGER->findImage(_acList.front())->setFrameY(_idx_y);
            if (_cnt % _sync[_acList.front()].timing == 0)
            {
                _idx_x++;
                if (_idx_x > IMAGEMANAGER->findImage(_acList.front())->getMaxFrameX())
                {
                    //if (!strcmp(_acList.front(), "Acolyte_death") && getState()[DIE_ENEMY])
                    //    _die = true;//setState(DIE_ENEMY, true);
                    _acList.pop_front();
                    if (!_acList.empty())
                    {
                        _idx_x = 0;
                        setAction(_acList.front());
                        _acState.reset();
                    }
                    else
                    {
                        if (getState()[DIE_ENEMY])
                            _die = true;
                        _acState.reset();
                        _hit = false;
                        
                        setState(IDLE_ENEMY, true);
                        setAction("Acolyte_walk");

                        if (_die) setState(DIE_ENEMY, true);
                    }
                }
                if (!_acList.empty())
                    IMAGEMANAGER->findImage(_acList.front())->setFrameX(_idx_x);
            }
        }
    }

    attack();
}

void Acolyte::attack(void)
{
    if (_acState[ATTACK_ENEMY])
    {
        if (_isLeft)
        {
            if (_idx_x < (getMaxFrame() - 6) && _idx_x >(getMaxFrame() - 15))
            {
                _acolytePos.x -= 5;
                _canAttack = true;
            }
            else _canAttack = false;
        }
        else
        {
            if (_idx_x > 6 && _idx_x < 15)
            {
                _acolytePos.x += 5;
                _canAttack = true;
            }
            else _canAttack = false;
        }
    }
}
void Acolyte::render(HDC hdc)
{
    if (_acList.empty())
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _acolytePos.x + _sync[_strAction].leftMove.x, 
                _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() + _sync[_strAction].leftMove.y,
                _idx_x, _idx_y);

            _acolyte = RectMakeCenter(_acolytePos.x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                80, 250);
        }
        else
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _acolytePos.x + _sync[_strAction].rightMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() + _sync[_strAction].rightMove.y,
                _idx_x, _idx_y);

            _acolyte = RectMakeCenter(_acolytePos.x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].rightMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].rightMove.y,
                80, 250);
        }
    }
    else
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_acList.front(), hdc,
                _acolytePos.x + _sync[_acList.front()].leftMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_acList.front())->getFrameHeight() + _sync[_acList.front()].leftMove.y,
                _idx_x, _idx_y);

            _acolyte = RectMakeCenter(_acolytePos.x + IMAGEMANAGER->findImage(_acList.front())->getFrameWidth() / 2 + _sync[_acList.front()].leftMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_acList.front())->getFrameHeight() / 2 + _sync[_acList.front()].leftMove.y,
                80, 250);
        }
        else
        {
            IMAGEMANAGER->frameRender(_acList.front(), hdc,
                _acolytePos.x + _sync[_acList.front()].rightMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_acList.front())->getFrameHeight() + _sync[_acList.front()].rightMove.y,
                _idx_x, _idx_y);

            _acolyte = RectMakeCenter(_acolytePos.x + IMAGEMANAGER->findImage(_acList.front())->getFrameWidth() / 2 + _sync[_acList.front()].rightMove.x,
                _acolytePos.y - IMAGEMANAGER->findImage(_acList.front())->getFrameHeight() / 2 + _sync[_acList.front()].rightMove.y,
                80, 250);
        }
    }
    
    _attackBoundary[0] = RectMake(_acolyte.left - 150, _acolytePos.y - 80, 150, 80);
    _attackBoundary[1] = RectMake(_acolyte.right, _acolytePos.y - 80, 150, 80);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);


        DrawRectMake(hdc, _acolyte);
        
        _stprintf_s(_loc, "x: %d y: %d", _acolytePos.x, _acolytePos.y);
        TextOut(hdc, _acolyte.left, _acolyte.top, _loc, strlen(_loc));
        TextOut(hdc, _acolyte.left, _acolyte.top + 20, _strAction, strlen(_strAction));
        
        if (_acState[ATTACK_ENEMY])
        {
            DrawRectMake(hdc, _attack);
        }
        myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _attackBoundary[0]);
        DrawRectMake(hdc, _attackBoundary[1]);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }

    cout << "a" << getState()[DIE_ENEMY] << endl;
}
