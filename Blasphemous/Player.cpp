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
    IMAGEMANAGER->addFrameImage("FALLING", "Resources/Image/Penitent/penitent_falling_loop.bmp",
        177 * 2, 152 * 2, 3, 2, true, MAGENTA);
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
    IMAGEMANAGER->addFrameImage("ATTACK_CROUCH", "Resources/Image/Penitent/penitent_crouch_attack_anim.bmp",
        1428 * 2, 132 * 2, 12, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_DODGE", "Resources/Image/Penitent/penitent_dodge_attack.bmp",
        2048 * 2, 512 * 2, 8, 4, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_COMBO", "Resources/Image/Penitent/penitent_three_hits_combo.bmp",
        6132 * 2, 154 * 2, 28, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PUSHBACK", "Resources/Image/Penitent/penitent_pushback_anim.bmp",
        1748 * 2, 152 * 2, 19, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PARRY", "Resources/Image/Penitent/penitent_parry_failed.bmp",
        740 * 2, 144 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PORTION", "Resources/Image/Penitent/penitent_healthposion_anim.bmp",
        3330 * 2, 280 * 2, 37, 2, true, MAGENTA);

    IMAGEMANAGER->addImage("Profile", "Resources/Image/Sheet/PlayerPortrait_activePrayer.bmp",
        88 * 2, 58 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("HP", "Resources/Image/Sheet/HealthBar.bmp", 
        132 * 2, 4 * 2, true, MAGENTA);

    IMAGEMANAGER->addImage("flask_full", "Resources/Image/Sheet/flask_full.bmp",
        11 * 2, 17 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("flask_empty", "Resources/Image/Sheet/flask_empty.bmp",
        11 * 2, 17 * 2, true, MAGENTA);

    _plPos_x = WINSIZE_X / 2 - 400;
    _plPos_y = WINSIZE_Y / 2 - 100;

    //_plPos = { WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 100 };

    _cnt = _idx_x = _idx_y = 0;
    _isLeft = _isGround = _isFixed = false;

    _centerX = _centerY = 0.0f;
    //_center = { 0, 0 };
    _tempX = _tempY = 0.0f;

    timer = time(NULL);
    localtime_s(&t, &timer);

    _hp = 100; 
    _portion = 5;

    for (int i = 0; i < MAX_STATE; i++)
    {
        setState(i, false);
    }

    wsprintf(_strAction, "IDLE");
    initTiming();

    return S_OK;
}

void Player::initTiming(void)
{
    _timing.insert(make_pair("JUMP", 10));
    _timing.insert(make_pair("JUMP_FORWARD", 6));
    _timing.insert(make_pair("ATTACK", 4));
    _timing.insert(make_pair("ATTACK_JUMP", 6));
    _timing.insert(make_pair("ATTACK_CROUCH", 5));
    _timing.insert(make_pair("ATTACK_DODGE", 4));
    _timing.insert(make_pair("ATTACK_COMBO", 5));
    _timing.insert(make_pair("PARRY", 5));
    _timing.insert(make_pair("PUSHBACK", 4));
    _timing.insert(make_pair("DODGE", 2));
    _timing.insert(make_pair("CROUCH_DOWN", 3));
    _timing.insert(make_pair("CROUCH_UP", 3));
    _timing.insert(make_pair("PORTION", 4));
}

void Player::playerAction(void)
{
    _centerX = _plPos_x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2;
    _centerY = _plPos_y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2;

    //_center.x = _plPos.x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2;
    //_center.y = _plPos.y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2;

    _player = RectMakeCenter(_centerX, _centerY,
        IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
        IMAGEMANAGER->findImage(_strAction)->getFrameHeight());

    if (KEYMANAGER->isStayKeyDown('A'))
    {
        _isLeft = true;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (!strcmp(_strAction, "JUMP"))
        {
            if (!isEmpty())
                _actionList.pop_front();
            _actionList.push_back("JUMP_FORWARD");
            setAction("JUMP_FORWARD");

            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("JUMP_FORWARD")->getMaxFrameX() - 5;
            else
                _idx_x = 6;
        }
        if (_plPos_x > 0)
            _plPos_x -= 4.0f;
    }
    if (KEYMANAGER->isStayKeyDown('D'))
    {
        _isLeft = false;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos_x < WINSIZE_X)
            _plPos_x += 4.0f;
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

    /*if (KEYMANAGER->isStayKeyDown('A') && !_isFixed)
    {
        _isLeft = true;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos.x > 0)
            _plPos.x -= 5;
    }
    if (KEYMANAGER->isStayKeyDown('D') && !_isFixed)
    {
        _isLeft = false;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos.x < WINSIZE_X)
            _plPos.x += 5;
    }*/
    /*if (KEYMANAGER->isStayKeyDown('S'))
    {
        setState(CROUCH, true);
        if (!_plState.none())
            setAction("CROUCH_DOWN");
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _plState.reset();
        setAction("IDLE");
    }*/

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
    if (KEYMANAGER->isOnceKeyDown('J') && isEmpty())
    {
        setState(PARRY, true);
        setAction("PARRY");
        _actionList.push_back("PARRY");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("PARRY")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('F') && isEmpty() && _portion > 0)
    {
        setState(PORTION, true);
        _actionList.push_back("PORTION");
        setAction("PORTION");
        _portion--;

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("PORTION")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_plState[JUMP])
    {
        _isFixed = true;
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

    /*if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_plState[JUMP])
    {
        _tempY = _plPos.y;
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
    }*/
    if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && !_plState[DODGE] && !_isFixed)
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
            if (!isEmpty())
                _actionList.pop_front();
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
        else if (_plState[CROUCH])
        {
            setState(ATTACK, true);
            setAction("ATTACK_CROUCH");
            _actionList.push_back("ATTACK_CROUCH");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("ATTACK_CROUCH")->getMaxFrameX();
            else
                _idx_x = 0;
        }

        else
        {
            setState(ATTACK, true);
            setAction("ATTACK_COMBO");
            _actionList.push_back("ATTACK_COMBO");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("ATTACK_COMBO")->getMaxFrameX();
            else
                _idx_x = 0;
        }
    }
    if (_plState[HIT] && isEmpty())
    {
        _actionList.push_back("PUSHBACK");
        _actionList.push_back("CROUCH_UP");
        setAction("PUSHBACK");

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("PUSHBACK")->getMaxFrameX();
        else
            _idx_x = 0;
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
           if (_cnt % _timing.find(_actionList.front())->second == 0)
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
                       _isFixed = false;
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
           if (_cnt % _timing.find(_actionList.front())->second == 0)
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
                       _isFixed = false;
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
            if (!strcmp(_strAction, "JUMP_FORWARD"))
            {
                if (_idx_x > getMaxFrameX() - 6)
                    _plPos_y -= 10.0f;
            }
            if (!strcmp(_strAction, "JUMP"))
            {
                if (_tempY - _plPos_y < 150)
                    _plPos_y -= 10.0f;
                else if (_tempY <= _plPos_y)
                    setAction("IDLE");
                else
                    setAction("FALLING");
            }
        }
        else
        {
            if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x < 6)
                _plPos_y -= 10.0f;
            if (!strcmp(_strAction, "JUMP"))
            {
                if (_tempY - _plPos_y < 150)
                    _plPos_y -= 10.0f;
                else
                    setAction("FALLING");
            }
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
            _plPos_x -= 8.5f;
        }
        else
        {
            _plPos_x += 8.5f;
        }
    }

    if (_plState[HIT])
    {
        if (_isLeft)
        {
            if (!strcmp(_strAction, "PUSHBACK") && _idx_x > getMaxFrameX() - 6)
                _plPos_x += 5.0f;
        }
        else
        {
            if (!strcmp(_strAction, "PUSHBACK") && _idx_x < 6)
                _plPos_x -= 5.0f;
        }
    }
    //if (_plState[JUMP])
    //{
    //    if (_isLeft)
    //    {
    //        if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x > getMaxFrameX() - 6)
    //            _plPos.y -= 10;
    //        else if (!strcmp(_strAction, "JUMP"))
    //        {

    //        }
    //    }
    //    else
    //    {
    //        if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x < 6)
    //            _plPos.y -= 10;
    //    }
    //    //else if(_plPos_y < _tempY - 180)
    //    //{
    //    //    _plState.reset();
    //    //    setAction("IDLE");
    //    //}
    //    /*if (_plPos_y < _tempY - 180)
    //    {
    //        _plState.reset();
    //        setAction("IDLE");
    //    }*/
    //}
    //if (_plState[DODGE])
    //{
    //    if (_isLeft)
    //    {
    //        _plPos.x -= 8;
    //    }
    //    else
    //    {
    //        _plPos.x += 8;
    //    }
    //}
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
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
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
    
    cout << _hp << endl;
    cout << "hit"<<_plState[HIT] << endl;
    cout <<"attack"<< _plState[ATTACK] << endl;
    cout <<"parry"<< _plState[PARRY] << endl;
    cout << _plPos_y << endl;

}

void Player::renderProfile(HDC hdc)
{ 
    IMAGEMANAGER->render("HP", hdc, 120, 52);
    IMAGEMANAGER->render("Profile", hdc, 30, 30);
    for (int i = 0; i < 5; i++)
    {
        if (i < _portion)
        {
            IMAGEMANAGER->render("flask_full", hdc, 160 + 35 * i, 100);
        }
        else
        {
            IMAGEMANAGER->render("flask_empty", hdc, 160 + 35 * i, 100);
        }
    }
}