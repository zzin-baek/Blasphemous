#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    IMAGEMANAGER->addFrameImage("IDLE", "Resources/Image/Penitent/penitent_idle_anim.bmp",
        871 * 2, 146 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("RUNNING", "Resources/Image/Penitent/penitent_running_anim.bmp",
        1092 * 2, 144 * 2, 14, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("JUMP", "Resources/Image/Penitent/penitent_jump_anim.bmp",
        235 * 2, 162 * 2, 5, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("JUMP_FORWARD", "Resources/Image/Penitent/penitent_jump_forward_anim.bmp",
        1230 * 2, 164 * 2, 15, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("DODGE", "Resources/Image/Penitent/penitent_dodge_anim.bmp",
        1261 * 2, 148 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("CROUCH_DOWN", "Resources/Image/Penitent/penitent_crouch_anim.bmp",
        567 * 2, 138 * 2, 7, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("CROUCH_UP", "Resources/Image/Penitent/penitent_crouch_up_anim.bmp",
        405 * 2, 144 * 2, 5, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("HANGON", "Resources/Image/Penitent/penitent_hangonledge_anim.bmp",
        1872 * 2, 166 * 2, 18, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("CLIMB", "Resources/Image/Penitent/penitent_climbledge_reviewed.bmp",
        1020 * 2, 262 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK", "Resources/Image/Penitent/penitent_attack_combo.bmp",
        1364 * 2, 144 * 2, 11, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_JUMP", "Resources/Image/Penitent/penitent_jumping_attack.bmp",
        1290 * 2, 188 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_DODGE", "Resources/Image/Penitent/penitent_dodge_attack.bmp",
        2048 * 2, 512 * 2, 8, 4, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("COMBO_ATTACK", "Resources/Image/Penitent/penitent_three_hits_combo.bmp",
        6132 * 2, 154 * 2, 28, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PARRY", "Resources/Image/Penitent/penitent_parry_failed.bmp",
        740 * 2, 144 * 2, 10, 2, true, MAGENTA);

    _plPos_x = WINSIZE_X / 2 - 300;
    _plPos_y = WINSIZE_Y / 2 - 100;

    _cnt = _idx_x = _idx_y = 0;
    _isLeft = _isGround = _isFixed = false;

    _centerX = _centerY = 0.0f;
    _tempX = _tempY = 0.0f;

    for (int i = 0; i < MAX_STATE; i++)
    {
        setState(i, false);
    }

    wsprintf(_strAction, "IDLE");

    return S_OK;
}

void Player::playerAction(void)
{
    _centerX = _plPos_x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2;
    _centerY = _plPos_y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2;

    _player = RectMakeCenter(_centerX, _centerY,
        IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
        IMAGEMANAGER->findImage(_strAction)->getFrameHeight());

    collision[0] = RectMakeCenter(_player.left, _centerY, 10, 10);
    collision[1] = RectMakeCenter(_player.right, _centerY, 10, 10);
    collision[2] = RectMakeCenter(_centerX, _player.bottom, 10, 10);

    if (KEYMANAGER->isStayKeyDown('A') && !_isFixed)
    {
        _isLeft = true;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos_x > 0)
            _plPos_x -= 5.0f;
    }
    if (KEYMANAGER->isStayKeyDown('D') && !_isFixed)
    {
        _isLeft = false;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos_x < WINSIZE_X)
            _plPos_x += 5.0f;
    }
    if (KEYMANAGER->isStayKeyDown('S'))
    {
        setState(CROUCH, true);
        if (!_plState.none())
            setAction("CROUCH_DOWN");
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _plState.reset();
        setAction("IDLE");
    }

    if (KEYMANAGER->isOnceKeyUp('S') && isEmpty())
    {
        setState(CROUCH, false);
        setAction("CROUCH_UP");
        _actionList.push_back("CROUCH_UP");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("CROUCH_UP")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('J'))
    {
        setState(PARRY, true);
        _actionList.push_back("PARRY");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("PARRY")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_plState[JUMP])
    {
        _tempY = _plPos_y;
        if (_plState[WALK])
        {
            setState(JUMP, true);
            setAction("JUMP_FORWARD");
            _actionList.push_back("JUMP_FORWARD");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("JUMP_FORWARD")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        else if (_plState[DODGE])
        {
            setAction("JUMP_FORWARD");
            setState(DODGE, false);
            setState(JUMP, true);
            _actionList.pop_front();
            _actionList.push_back("JUMP_FORWARD");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("JUMP_FORWARD")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        else if (_plState.none())
        {
            setState(JUMP, true);
            setAction("JUMP");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("JUMP")->getMaxFrameX();
            else
                _idx_x = 0;
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
    {
        _tempX = _plPos_x;
        setState(DODGE, true);
        _actionList.push_back("DODGE");
        setAction("DODGE");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("DODGE")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('K') && !_plState[ATTACK])
    {
        if (_plState[JUMP])
        {
            setState(ATTACK, true);
            setAction("ATTACK_JUMP");
            _actionList.push_back("ATTACK_JUMP");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("ATTACK_JUMP")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        else if (_plState[DODGE])
        {
            setState(ATTACK, true);
            setAction("ATTACK_DODGE");
            _actionList.push_back("ATTACK_DODGE");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("ATTACK_DODGE")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        else
        {
            setState(ATTACK, true);
            setAction("ATTACK");
            _actionList.push_back("ATTACK");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("ATTACK")->getMaxFrameX();
            else
                _idx_x = 0;
        }
    }

   _cnt++;
   if (_actionList.empty())
   {
       if (_isLeft)
       {
           _idx_y = 1;
           IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
           if (_cnt % 5 == 0)
           {
               _idx_x--;
               if (_idx_x < 0)
               {
                   if (strcmp(_strAction, "CROUCH_DOWN") == 0)
                       _idx_x = 0;
                   else _idx_x = getMaxFrameX();
               }
               IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx_x);
           }
       }
       else
       {
           _idx_y = 0;
           IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
           if (_cnt % 5 == 0)
           {
               _idx_x++;
               if (_idx_x > getMaxFrameX())
               {
                   if (strcmp(_strAction, "CROUCH_DOWN") == 0)
                       _idx_x = getMaxFrameX();
                   else _idx_x = 0;
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
           IMAGEMANAGER->findImage(_actionList.front().c_str())->setFrameY(_idx_y);
           if (_cnt % 5 == 0)
           {
               _idx_x--;
               if (_idx_x < 0)
               {
                   _actionList.pop_front();
                   if (!_actionList.empty())
                       _idx_x = IMAGEMANAGER->findImage(_actionList.front().c_str())->getMaxFrameX();
                   else
                   {
                       _plState.reset();
                       setAction("IDLE");
                   }
               }
               if (!_actionList.empty())
                    IMAGEMANAGER->findImage(_actionList.front().c_str())->setFrameX(_idx_x);
           }
       }
       else
       {
           _idx_y = 0;
           IMAGEMANAGER->findImage(_actionList.front().c_str())->setFrameY(_idx_y);
           if (_cnt % 5 == 0)
           {
               _idx_x++;
               if (_idx_x > IMAGEMANAGER->findImage(_actionList.front())->getMaxFrameX())
               {
                   _actionList.pop_front();
                   if (!_actionList.empty())
                        _idx_x = 0;
                   else
                   {
                       _plState.reset();
                       setAction("IDLE");
                   }
               }
               if (!_actionList.empty())
                    IMAGEMANAGER->findImage(_actionList.front().c_str())->setFrameX(_idx_x);
           }
       }
   }
}

void Player::playerMove(void)
{
    if (_plState[JUMP])
    {
        if (_isLeft)
        {
            if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x > getMaxFrameX() - 6)
                _plPos_y -= 10.0f;
            else if (!strcmp(_strAction, "JUMP"))
            {

            }
        }
        else
        {
            if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x < 6)
                _plPos_y -= 10.0f;
        }
        //else if(_plPos_y < _tempY - 180)
        //{
        //    _plState.reset();
        //    setAction("IDLE");
        //}
        /*if (_plPos_y < _tempY - 180)
        {
            _plState.reset();
            setAction("IDLE");
        }*/
    }
    if (_plState[DODGE])
    {
        if (_isLeft)
        {
            _plPos_x -= 8.0f;
        }
        else
        {
            _plPos_x += 8.0f;
        }
    }
}

Player::~Player()
{
    
}

void Player::renderPlayer(HDC hdc)
{
    if(_actionList.empty())
        IMAGEMANAGER->frameRender(_strAction, hdc, _plPos_x, _plPos_y, _idx_x, _idx_y);
    else
        IMAGEMANAGER->frameRender(_actionList.front().c_str(), hdc, _plPos_x, _plPos_y, _idx_x, _idx_y);
    if (KEYMANAGER->isToggleKey(VK_CONTROL))
    {
        collisionRect(hdc);

        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _player);
        _stprintf_s(_loc, "x: %.2f y: %.2f", _plPos_x, _plPos_y);
        TextOut(hdc, _plPos_x, _plPos_y, _loc, strlen(_loc));
        TextOut(hdc, _plPos_x, _plPos_y + 20, _strAction, strlen(_strAction));

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
    //cout << _actionList.size() << endl;
}

void Player::collisionRect(HDC hdc)
{
    for (int i = 0; i < 3; i++)
    {
        DrawRectMake(hdc, collision[i]);
    }
}
