#include "Stdafx.h"
#include "Stoner.h"

HRESULT Stoner::init(void)
{
	IMAGEMANAGER->addFrameImage("Stoner_rising", "Resources/Image/Enemy/stoner_rising_anim.bmp",
		1034 * 2, 106 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_idle", "Resources/Image/Enemy/stoner_idle_anim.bmp",
		1128 * 2, 106 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_leftright", "Resources/Image/Enemy/stoner_leftright_anim.bmp",
		658 * 2, 106 * 2, 7, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_attack", "Resources/Image/Enemy/stoner_attack_anim.bmp",
		1960 * 2, 148 * 2, 20, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_death", "Resources/Image/Enemy/stoner_death_anim.bmp",
		1952 * 2, 162 * 2, 16, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Rock", "Resources/Image/Enemy/thrown_rock_anim.bmp",
		136 * 2, 68 * 2, 8, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Rock_landing", "Resources/Image/Enemy/rock_ground_landing_anim.bmp",
		441 * 2, 116 * 2, 7, 2, true, MAGENTA);

	_cnt = 0;
	_idx = { 0, 0 };
	_isRising = _onceRock = false;
    _die = _hit = _isAttack = false;

	_stState.reset();
	_hp = 30;

    wsprintf(_strAction, "Stoner_idle");

    initSync();

	return S_OK;
}

HRESULT Stoner::init(float locX, float locY)
{
	_stonerPos = { locX, locY };
	return S_OK;
}

void Stoner::initSync(void)
{
	_sync.insert({ "Stoner_rising", {13, {0, 0}, {0, 0}} });
	_sync.insert({ "Stoner_idle", {10, {0, 0}, {0, 0}} });
	_sync.insert({ "Stoner_leftright", {10, {0, 0}, {0, 0}} });
	_sync.insert({ "Stoner_attack", {10, {-5, -21}, {-5, -21}} });
	_sync.insert({ "Stoner_death", {7, {-5, -32}, {-5, -32}} });
}

void Stoner::move(void)
{
    _attackBoundary = RectMakeCenter(_stonerPos.x, _stonerPos.y, 700, 700);

    _cnt++;
    if (_isRising)
	{
        if (_stonerPos.x <= PLAYER->getCenterX())
        {
            if (_isLeft && strcmp(_strAction, "Stoner_attack") && isEmpty())
            {
                _stList.push_back("Stoner_leftright");
                _isLeft = false;

                if (_isLeft)
                    _idx.x = IMAGEMANAGER->findImage("Stoner_leftright")->getMaxFrameX();
                else
                    _idx.x = 0;
            }
        }
        else
        {
            if (!_isLeft && strcmp(_strAction, "Stoner_attack") && isEmpty())
            {
                _stList.push_back("Stoner_leftright");
                _isLeft = true;

                if (_isLeft)
                    _idx.x = IMAGEMANAGER->findImage("Stoner_leftright")->getMaxFrameX();
                else
                    _idx.x = 0;
            }
        }

        //if (_stState[HIT_ENEMY] && !_hit)
        //{
        //    _stList.clear();
        //    //_acState.reset();
        //    setState(ATTACK_ENEMY, false);
        //    _hit = true;
        //}


        if (getState()[ATTACK_ENEMY])
        {
            if (_cnt % 100 == 0)
            {
                if (isEmpty())
                {
                    _stList.push_back("Stoner_attack");
                    setAction("Stoner_attack");

                    if (_isLeft)
                        _idx.x = IMAGEMANAGER->findImage("Stoner_attack")->getMaxFrameX();
                    else
                        _idx.x = 0;
                }
            }
        }

        if (!strcmp(_strAction, "Stoner_attack"))
        {
            if (_isLeft)
            {
                if (_idx.x == IMAGEMANAGER->findImage("Stoner_attack")->getMaxFrameX() - 15 && !_onceRock)
                {
                    float ag;
                    for (int i = 0; i < MAX_ROCK; i++)
                    {
                        if (_rock[i].shoot) continue;

                        ag = atan2((PLAYER->getCenterY() - (_stonerPos.y - 100)),
                            (_stonerPos.x - PLAYER->getCenterX()));

                        _rock[i].shoot = true;
                        _rock[i].pos = { _stonerPos.x, _stonerPos.y - 100 };
                        _rock[i].rock = RectMakeCenter(_rock[i].pos.x, _rock[i].pos.y, 30, 30);
                        _rock[i].idx = { 0, 0 };
                        _rock[i].cnt = 0;
                        _rock[i].angle = ag * 180 / PI - 180;
                        _rock[i].cycle.push_back("Rock");

                        break;
                    }
                    _onceRock = true;
                }
            }
            else
            {
                if (_idx.x == 15 && !_onceRock)
                {
                    float ag;
                    for (int i = 0; i < MAX_ROCK; i++)
                    {
                        if (_rock[i].shoot) continue;

                        ag = atan2((PLAYER->getCenterY() - (_stonerPos.y - 100)),
                            (_stonerPos.x - PLAYER->getCenterX()));

                        _rock[i].shoot = true;
                        _rock[i].pos = { _stonerPos.x, _stonerPos.y - 100 };
                        _rock[i].rock = RectMakeCenter(_rock[i].pos.x, _rock[i].pos.y, 30, 30);
                        _rock[i].idx = { 0, 0 };
                        _rock[i].cnt = 0;
                        _rock[i].angle = ag * 180 / PI - 180;
                        _rock[i].cycle.push_back("Rock");

                        break;
                    }
                    _onceRock = true;
                }           
            }
        }

        rockMove();
        rockCycle();

        if (_hp <= 0 && !getState()[DIE_ENEMY])
        {
            setState(IDLE_ENEMY, false);
            setState(DIE_ENEMY, true);
            //_die = true;

            _stList.clear();
            _stList.push_back("Stoner_death");

            if (_isLeft)
                _idx.x = IMAGEMANAGER->findImage("Stoner_death")->getMaxFrameX();
            else
                _idx.x = 0;
        }

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
                if (_cnt % _sync[_stList.front()].timing == 0)
                {
                    _idx.x--;
                    _onceRock = false;
                    if (_idx.x < 1)
                    {              
                        _stList.pop_front();
                        if (!_stList.empty())
                        {
                            _idx.x = IMAGEMANAGER->findImage(_stList.front())->getMaxFrameX();
                            setAction(_stList.front());
                            _stState.reset();
                        }
                        else
                        {
                            if (getState()[DIE_ENEMY])
                                _die = true;

                            _stState.reset();
                            _hit = false;

                            setState(IDLE_ENEMY, true);
                            setAction("Stoner_idle");

                            if (_die) setState(DIE_ENEMY, true);
                        }
                    }
                    if (!_stList.empty())
                    {
                        IMAGEMANAGER->findImage(_stList.front())->setFrameY(_idx.y);
                        IMAGEMANAGER->findImage(_stList.front())->setFrameX(_idx.x);
                    }
                }
            }
            else
            {
                _idx.y = 0;
                if (_cnt % _sync[_stList.front()].timing == 0)
                {
                    _idx.x++;
                    _onceRock = false;
                    if (_idx.x > IMAGEMANAGER->findImage(_stList.front())->getMaxFrameX())
                    {
                        _stList.pop_front();
                        if (!_stList.empty())
                        {
                            _idx.x = 0;
                            setAction(_stList.front());
                            _stState.reset();
                        }
                        else
                        {
                            if (getState()[DIE_ENEMY])
                                _die = true;

                            _stState.reset();
                            _hit = false;

                            setState(IDLE_ENEMY, true);
                            setAction("Stoner_idle");

                            if (_die) setState(DIE_ENEMY, true);
                        }
                    }
                    if (!_stList.empty())
                    {
                        IMAGEMANAGER->findImage(_stList.front())->setFrameY(_idx.y);
                        IMAGEMANAGER->findImage(_stList.front())->setFrameX(_idx.x);
                    }
                }
            }
        }

	}
}

void Stoner::rockMove(void)
{
    POINTF center;

    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (_rock[i].shoot)
        {
            center.x = _rock[i].pos.x + 3 * cos((_rock[i].angle * PI / 180));
            center.y = _rock[i].pos.y - 3 * sin((_rock[i].angle * PI / 180));

            _rock[i].pos = { center.x, center.y };
            _rock[i].rock = RectMakeCenter(_rock[i].pos.x, _rock[i].pos.y, 30, 30);
        }
    }

    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (_rock[i].shoot)
        {   // 픽셀충돌로 바꾸기
            if (_rock[i].pos.y > 600 || _rock[i].pos.y < -30)
                _rock[i].broke = true;
        }
    }
}

void Stoner::rockCycle(void)
{
    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (_rock[i].shoot && !_rock[i].cycle.empty() && _cnt % 2 == 0)
        {
            _rock[i].cnt++;

            _rock[i].idx.x = _rock[i].cnt % (IMAGEMANAGER->findImage(_rock[i].cycle.front())->getMaxFrameX() + 1);

            if (_rock[i].cnt > (IMAGEMANAGER->findImage(_rock[i].cycle.front())->getMaxFrameX() + 1) - 1)
            {
                _rock[i].cnt = 0;
                if (!strcmp(_rock[i].cycle.front(), "Rock_landing"))
                {
                    _rock[i].shoot = _rock[i].broke = false;
                    _rock[i].pos = { 0, 0 };

                    _onceRock = false;
                }
                _rock[i].cycle.pop_front();
            }

            if (!_rock[i].cycle.empty())
            {
                IMAGEMANAGER->findImage(_rock[i].cycle.front())->setFrameX(_rock[i].idx.x);
                IMAGEMANAGER->findImage(_rock[i].cycle.front())->setFrameY(_rock[i].idx.y);
            }
            else
            {
                if (_rock[i].shoot)
                {
                    if (_rock[i].broke)
                        _rock[i].cycle.push_back("Rock_landing");
                    else
                        _rock[i].cycle.push_back("Rock");
                }
            }
        }
    }
}

void Stoner::rockCollision(void)
{
    RECT _rt;
    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (!_rock[i].shoot) continue;
        if (_rock[i].broke) continue;

        if (IntersectRect(&_rt, &_rock[i].rock, &PLAYER->getRect()) && PLAYER->getState()[ATTACK])
        {
                _rock[i].broke = true;            
        }

        if (IntersectRect(&_rt, &_rock[i].rock, &PLAYER->getHitBox()) && !PLAYER->getState()[ATTACK])
        {
            if (!PLAYER->getState()[HIT] && !PLAYER->getHit())
            {
                PLAYER->setHit(true);
                PLAYER->setHP(PLAYER->getHP() - 5);
                _rock[i].broke = true;
            }
        }
    }
}

void Stoner::setRockPos(int x, int y)
{
    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (!_rock[i].shoot) continue;

        _rock[i].pos.x += x;
        _rock[i].pos.y += y;

        _rock[i].rock = RectMakeCenter(_rock[i].pos.x, _rock[i].pos.y, 30, 30);
    }
}

void Stoner::render(HDC hdc)
{
    if (_isRising)
    {
        if (_stList.empty())
        {
            if (_isLeft)
            {
                IMAGEMANAGER->frameRender(_strAction, hdc, 
                    _stonerPos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                    _stonerPos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                    _idx.x, _idx.y);

                _stoner = RectMakeCenter(_stonerPos.x + _sync[_strAction].leftMove.x,
                    _stonerPos.y + _sync[_strAction].leftMove.y, IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                    IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
            }
            else
            {
                IMAGEMANAGER->frameRender(_strAction, hdc,
                    _stonerPos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2 + _sync[_strAction].leftMove.x,
                    _stonerPos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2 + _sync[_strAction].leftMove.y,
                    _idx.x, _idx.y);

                _stoner = RectMakeCenter(_stonerPos.x + _sync[_strAction].rightMove.x,
                    _stonerPos.y + _sync[_strAction].rightMove.y, IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                    IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
            }
        }
        else
        {
            if (_isLeft)
            {
                IMAGEMANAGER->frameRender(_stList.front(), hdc,
                    _stonerPos.x - IMAGEMANAGER->findImage(_stList.front())->getFrameWidth() / 2 + _sync[_stList.front()].leftMove.x,
                    _stonerPos.y - IMAGEMANAGER->findImage(_stList.front())->getFrameHeight() / 2 + _sync[_stList.front()].leftMove.y,
                    _idx.x, _idx.y);

                _stoner = RectMakeCenter(_stonerPos.x + _sync[_stList.front()].leftMove.x,
                    _stonerPos.y + _sync[_stList.front()].leftMove.y, IMAGEMANAGER->findImage(_stList.front())->getFrameWidth(),
                    IMAGEMANAGER->findImage(_stList.front())->getFrameHeight());
            }
            else
            {
                IMAGEMANAGER->frameRender(_stList.front(), hdc,
                    _stonerPos.x - IMAGEMANAGER->findImage(_stList.front())->getFrameWidth() / 2 + _sync[_stList.front()].rightMove.x,
                    _stonerPos.y - IMAGEMANAGER->findImage(_stList.front())->getFrameHeight() / 2 + _sync[_stList.front()].rightMove.y,
                    _idx.x, _idx.y);

                _stoner = RectMakeCenter(_stonerPos.x + _sync[_stList.front()].rightMove.x,
                    _stonerPos.y + _sync[_stList.front()].rightMove.y, IMAGEMANAGER->findImage(_stList.front())->getFrameWidth(), 
                    IMAGEMANAGER->findImage(_stList.front())->getFrameHeight());
            }
        }
    }

    IMAGEMANAGER->render("ENEMY_HP_BAR", hdc, _stonerPos.x -30, _stonerPos.y - 70);
    IMAGEMANAGER->render("ENEMY_HP", hdc, _stonerPos.x -30 + 2, _stonerPos.y - 68, 0, 0,
        IMAGEMANAGER->findImage("ENEMY_HP")->getWidth() * _hp / 30, IMAGEMANAGER->findImage("ENEMY_HP")->getHeight());


    for (int i = 0; i < MAX_ROCK; i++)
    {
        if (_rock[i].shoot && !_rock[i].cycle.empty())
        {
            //_mask = RectMake(_fb[i]._center.x - 23, _fb[i]._center.y - 23, 130, 130);            
            IMAGEMANAGER->frameRender(_rock[i].cycle.front(), hdc,
                _rock[i].pos.x - 15, _rock[i].pos.y - 15, _rock[i].idx.x, _rock[i].idx.y);
        }
    }

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _attackBoundary);
        for (int i = 0; i < MAX_ROCK; i++)
        {
            if (!_rock[i].shoot) continue;
            DrawRectMake(hdc, _rock[i].rock);
        }

        _stprintf_s(_loc, "x: %.2f y: %.2f", _stonerPos.x, _stonerPos.y);
        TextOut(hdc, _stonerPos.x, _stonerPos.y, _loc, strlen(_loc));
        TextOut(hdc, _stonerPos.x, _stonerPos.y + 20, _strAction, strlen(_strAction));
        
        myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _stoner);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
