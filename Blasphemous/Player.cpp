#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    initImage();

    _cnt = _idx_x = _idx_y = 0;
    _isLeft = _isGround = _isFixed = _hold = _collect = false;
    _isAttack = _collected = _respawn = _hit = _parrying =false;

    _center = _temp = { 0.0f, 0.0f };

    _hp = 100; 
    _score, _parry = 0;
    _portion = 5;

    wsprintf(_strAction, "IDLE");
    initTiming();

    return S_OK;
}

HRESULT Player::init(int startX, int startY)
{
    _plPos.x = startX;
    _plPos.y = startY;

    for (int i = 0; i < MAX_STATE; i++)
    {
        setState(i, false);
    }

    return S_OK;
}

void Player::initImage(void)
{
    IMAGEMANAGER->addFrameImage("RESPAWN", "Resources/Image/Penitent/penitent_respawn_anim.bmp",
        1166 * 2, 708 * 2, 11, 4, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("RESPAWN2", "Resources/Image/Penitent/penitent_respawn2_anim.bmp",
        4558 * 2, 177 * 2, 43, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("IDLE", "Resources/Image/Penitent/penitent_idle_anim.bmp",
        871 * 2, 146 * 2, 13, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("RUNNING", "Resources/Image/Penitent/penitent_running_anim.bmp",
        1092 * 2, 144 * 2, 14, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("STOP", "Resources/Image/Penitent/penitent_stop_anim.bmp",
        581 * 2, 136 * 2, 7, 2, true, MAGENTA);
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
    IMAGEMANAGER->addFrameImage("LADDER", "Resources/Image/Penitent/penitent_ladder_climb_loop_anim.bmp",
        330 * 2, 156 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK", "Resources/Image/Penitent/penitent_attack_combo_1.bmp",
        1224 * 2, 144 * 2, 9, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_COMBO_2", "Resources/Image/Penitent/penitent_attack_combo_2.bmp",
        987 * 2, 136 * 2, 7, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_COMBO_3", "Resources/Image/Penitent/penitent_attack_combo_3.bmp",
        2292 * 2, 154 * 2, 12, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_JUMP", "Resources/Image/Penitent/penitent_jumping_attack.bmp",
        1290 * 2, 188 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_JUMP1", "Resources/Image/Penitent/penitent_jumping_attack1.bmp",
        645 * 2, 188 * 2, 5, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_JUMP2", "Resources/Image/Penitent/penitent_jumping_attack2.bmp",
        645 * 2, 188 * 2, 5, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_UPWARD", "Resources/Image/Penitent/penitent_upward_attack.bmp",
        810 * 2, 238 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_UPWARD_JUMP", "Resources/Image/Penitent/penitent_upward_attack_jump.bmp",
        720 * 2, 268 * 2, 9, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_CROUCH", "Resources/Image/Penitent/penitent_crouch_attack_anim.bmp",
        1428 * 2, 132 * 2, 12, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("ATTACK_DODGE", "Resources/Image/Penitent/penitent_dodge_attack.bmp",
        4850 * 2, 216 * 2, 25, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PUSHBACK", "Resources/Image/Penitent/penitent_pushback_anim.bmp",
        1748 * 2, 152 * 2, 19, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PARRY", "Resources/Image/Penitent/penitent_parry_failed.bmp",
        740 * 2, 144 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PARRY_SUCCESS", "Resources/Image/Penitent/penitent_parry_anim.bmp",
        1617 * 2, 216 * 2, 11, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PARRY_SLIDE", "Resources/Image/Penitent/penitent_guardslide_anim.bmp",
        2080 * 2, 192 * 2, 20, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("COUNTER", "Resources/Image/Penitent/penitent_parry_counter.bmp",
        3154 * 2, 212 * 2, 19, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("PORTION", "Resources/Image/Penitent/penitent_healthposion_anim.bmp",
        3330 * 2, 280 * 2, 37, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("COLLECT", "Resources/Image/Penitent/penitent_collecting_object_anim.bmp",
        2470 * 2, 164 * 2, 26, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("DEATH", "Resources/Image/Penitent/penitent_death_anim.bmp",
        2760 * 2, 172 * 2, 24, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("DEATH_FALL", "Resources/Image/Penitent/penitent_death_by_fall_anim.bmp",
        1160 * 2, 128 * 2, 10, 2, true, MAGENTA);

    IMAGEMANAGER->addImage("Profile", "Resources/Image/Sheet/life_portrait.bmp",
        219 * 2, 58 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("Score", "Resources/Image/Sheet/score.bmp", 83 * 2, 48 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("HP", "Resources/Image/Sheet/HealthBar.bmp",
        136 * 2, 4 * 2, true, MAGENTA);

    IMAGEMANAGER->addImage("ENEMY_HP_BAR", "Resources/Image/Sheet/enemy_health_bar.bmp",
        34 * 2, 4 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("ENEMY_HP", "Resources/Image/Sheet/enemy_health_blood.bmp",
        32 * 2, 2 * 2, true, MAGENTA);

    IMAGEMANAGER->addImage("flask_full", "Resources/Image/Sheet/flask2_full.bmp",
        14 * 2, 21 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("flask_empty", "Resources/Image/Sheet/flask2_empty.bmp",
        14 * 2, 21 * 2, true, MAGENTA);
}

void Player::initTiming(void)
{
    // ## 기본적으로 왼쪽모습은 오른쪽 모습의 x + 50 
    _sync["RESPAWN2"] = { 5, {0, -195}, {-16, -194} };
    _sync["IDLE"] = { 5, {0 + 50, 0}, {0, 0} };
    _sync["RUNNING"] = { 3, {0 + 50, 0}, {0, 0} };
    _sync["STOP"] = { 4, {-10 + 50, 10}, {-10, 10} };
    _sync["FALLING"] = { 5, {0 + 50, 0}, {10, 0} };
    _sync["HANGON"] = { 5, {0, -50}, {50, -50} };
    _sync["CLIMB"] = { 5, {0, -150}, {50, -150} };
    _sync["LADDER"] = { 6, {50, 0}, {50, 0} };
    _sync["JUMP"] = { 6, {0 + 50, 0}, {30, 0} };
    _sync["JUMP_FORWARD"] = { 5, {0 + 50, -20}, {0, -20} };
    _sync["ATTACK"] = { 3, {-135 + 50, 2}, {0, 3} };
    _sync["ATTACK_JUMP"] = { 6, {-100 + 50, -80}, {0, -80} };
    _sync["ATTACK_JUMP1"] = { 4, {-100 + 50, -80}, {-20, -80} };
    _sync["ATTACK_JUMP2"] = { 6, {-100 + 50, -80}, {0, -80} };
    _sync["ATTACK_UPWARD"] = { 4, {-30 + 50, -92}, {8, -92} };
    _sync["ATTACK_UPWARD_JUMP"] = { 4, {0 + 50, -190}, {0, -190} };
    _sync["ATTACK_CROUCH"] = { 4, {-80 + 50, 20}, {-15, 20} };
    _sync["ATTACK_DODGE"] = { 3, {-240 + 50, -55}, {-5, -55} };
    _sync["ATTACK_COMBO_2"] = { 4, {-130 + 50, 10}, {-20, 10} };
    _sync["ATTACK_COMBO_3"] = { 4, {-310 + 50, -8}, {60, -8} };
    _sync["PARRY"] = { 4, {-10 + 50, 0}, {0, 0} };
    _sync["PARRY_SUCCESS"] = { 4, {-85, -60}, {-15, -60} };
    _sync["PARRY_SLIDE"] = { 3, {-42 + 50, -18}, {-29, -18} }; // -18
    _sync["COUNTER"] = { 4, {-180 + 50, -58}, {0, -58} };
    _sync["PUSHBACK"] = { 4, {-20 + 50, 10}, {-30, 10} };
    _sync["DODGE"] = { 2, {0 + 50, 0}, {0, 0} };
    _sync["CROUCH_DOWN"] = { 3, {0 + 50, 10}, {-25, 10} };
    _sync["CROUCH_UP"] = { 3, {0 + 50, 0}, {-25, 0} };
    _sync["PORTION"] = { 4, {-50 + 50, -125}, {0, -125} };
    _sync["COLLECT"] = { 5, {0, -6}, {-1, -6} };
    _sync["DEATH"] = { 5, {-23, -10}, {-12, -10} };
    _sync["DEATH_FALL"] = { 7, {-30, 60}, {-20, 60} };
}

void Player::playerAction(void)
{
    if (!_respawn && isEmpty())
    {
        _actionList.push_back("RESPAWN2");
    }

    _center.x = _plPos.x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2;
    _center.y = _plPos.y + IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2;

    if (strstr("ATTACK", _strAction))
        _isAttack = true;
    // 히트박스 설정
    if (_isLeft)
    {
        if (_isAttack || !strcmp(_strAction, "PARRY_SUCCESS") || !strcmp(_strAction, "COUNTER"))
            _hitBox = RectMake(_player.right - 130, _player.bottom - 130, 80, 130);
        else if (getState()[PORTION])
            _hitBox = RectMakeCenter(_center.x, _player.bottom - 75, 80, 130);
        else if (getState()[JUMP] && getState()[ATTACK])
            _hitBox = RectMake(_player.left, _player.bottom - 180, 80, 130);
        else
            _hitBox = RectMake(_player.left, _player.bottom - 130, 80, 130);
    }
    else
    {
        if (_isAttack || !strcmp(_strAction, "PARRY_SUCCESS") || !strcmp(_strAction, "COUNTER"))
            _hitBox = RectMake(_player.left + 70, _player.bottom - 130, 80, 130);
        else if (getState()[PORTION])
            _hitBox = RectMakeCenter(_center.x, _player.bottom - 75, 80, 130);
        else
            _hitBox = RectMake(_player.right - 80, _player.bottom - 130, 80, 130);
    }

    if (_isGround)
    {
        if (!strcmp(_strAction, "FALLING"))
        {
            setAction("IDLE");
            /*setAction("STOP");
            _actionList.push_back("STOP");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("STOP")->getMaxFrameX();
            else
                _idx_x = 0;
            */_plState.reset();
        }
    }
    else
    {
        if (_plState.none())
            setAction("FALLING");
    }


    if (_plState[DEATH_FALL])
    {
        //_actionList.clear();
        //_actionList.push_back("DEATH_FALL");
    }

    //cout << "hold"<<_hold << endl;
    if (KEYMANAGER->isStayKeyDown('A') && !strstr("ATTACK", _strAction) 
        && !_plState[DODGE] && !_plState[PARRY])
    {
        
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
        _isLeft = true;
        setState(WALK, true);
        if (!_plState[CROUCH] && !_plState[HIT])
            _plPos.x -= 4.0f;
    }
    if (KEYMANAGER->isStayKeyDown('D') && !strstr("ATTACK", _strAction)
        && !_plState[DODGE] && !_plState[PARRY])
    {
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
        _isLeft = false;
        setState(WALK, true);
        if (!_plState[CROUCH] && !_plState[HIT])
            _plPos.x += 4.0f;
    }
    if (KEYMANAGER->isStayKeyDown('S') && isEmpty())
    {
        setState(CROUCH, true);
        if (!_plState.none())
            setAction("CROUCH_DOWN");
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _plState.reset();
        setAction("IDLE");
        /* setAction("STOP");
        _actionList.push_back("STOP");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("STOP")->getMaxFrameX();
        else
            _idx_x = 0;*/
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

    // 패링 성공
    if (_parry && !_isFixed && !_parrying)
    { 
        if (!isEmpty())
            _actionList.pop_front();

        if (_parry == 1)
        {
            _isFixed = true;
            setAction("PARRY_SUCCESS");
            _actionList.push_back("PARRY_SUCCESS");
            _actionList.push_back("COUNTER");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("PARRY_SUCCESS")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        else if (_parry == 2)
        {
            _parrying = true;
            setAction("PARRY_SLIDE");
            _actionList.push_back("PARRY_SLIDE");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("PARRY_SLIDE")->getMaxFrameX();
            else
                _idx_x = 0;
        }
        _parry = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('F') && isEmpty() && _portion > 0)
    {
        setState(PORTION, true);
        _actionList.push_back("PORTION");
        setAction("PORTION");
        _portion--;
        _hp += 30;
        if (_hp > 100)
            _hp = 100;

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("PORTION")->getMaxFrameX();
        else
            _idx_x = 0;
    }

    if (KEYMANAGER->isOnceKeyDown('E') && _collect)
    {
        _actionList.push_back("COLLECT");
        _collected = true;
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("COLLECT")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    if (KEYMANAGER->isOnceKeyUp('E'))
        _collected = false;

    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_plState[JUMP])
    {
        //_isFixed = true;
        _temp.y = _plPos.y;
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
        else if (_plState.none() && isEmpty())
        {
            setState(JUMP, true);
            setAction("JUMP");
            _actionList.push_back("JUMP");
            if (_isLeft)
                _idx_x = IMAGEMANAGER->findImage("JUMP")->getMaxFrameX();
            else
                _idx_x = 0;
        }
    }

    if (KEYMANAGER->isStayKeyDown('W'))
    {
        setState(UP, true);

        /*if (!isEmpty())
            _actionList.pop_front();*/

        if (_hold)
        {
            _isFixed = true;
            //_hold = false;
            setState(LADDER, true);
            setAction("LADDER");
            _plPos.y -= 3.0f;
        }
       /* _actionList.push_back("HANGON");
        _actionList.push_back("CLIMB");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("HANGON")->getMaxFrameX();
        else
            _idx_x = 0;*/
    }
    if (KEYMANAGER->isOnceKeyUp('W') && _hold)
        setState(UP, false);

    if (KEYMANAGER->isOnceKeyDown(VK_SHIFT) && !_plState[DODGE] && isEmpty())
    {
        _temp.x = _plPos.x;
        setState(DODGE, true);
        _actionList.push_back("DODGE");
        //_actionList.push_back("STOP");
        setAction("DODGE");
        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("DODGE")->getMaxFrameX();
        else
            _idx_x = 0;
    }

    if (KEYMANAGER->isOnceKeyDown('K'))
    {
        if (!_plState[ATTACK])
        {
            if (_plState[JUMP])
            {
                setState(ATTACK, true);
                
                if (!isEmpty())
                    _actionList.clear();

                if (_plState[UP])
                {
                    setAction("ATTACK_UPWARD_JUMP");
                    _actionList.push_back("ATTACK_UPWARD_JUMP");

                    if (_isLeft)
                        _idx_x = IMAGEMANAGER->findImage("ATTACK_UPWARD_JUMP")->getMaxFrameX();
                    else
                        _idx_x = 0;
                }
                else
                {
                    setAction("ATTACK_JUMP1");
                    _actionList.push_back("ATTACK_JUMP1");
                    if (_isLeft)
                        _idx_x = IMAGEMANAGER->findImage("ATTACK_JUMP1")->getMaxFrameX();
                    else
                        _idx_x = 0;
                }
            }
            else if (_plState[UP])
            {
                setState(ATTACK, true);
                setAction("ATTACK_UPWARD");
                _actionList.push_back("ATTACK_UPWARD");
                if (_isLeft)
                    _idx_x = IMAGEMANAGER->findImage("ATTACK_UPWARD")->getMaxFrameX();
                else
                    _idx_x = 0;
            }
            else if (_plState[DODGE])
            {
                setState(ATTACK, true);
                setState(DODGE, false);
                setAction("ATTACK_DODGE");
                if (!isEmpty())
                    _actionList.clear();
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
                //setState(ATTACK, true);
                _attackTime.push_back(clock());
                cout << "dd" << endl;
                comboAttack();
            }
        }
        else
            _comboTime.push_back(clock());
    }
    if (!_plState[HIT] && _hit)
    {
        setState(HIT, true);
        setAction("PUSHBACK");

        if (!isEmpty())
            _actionList.clear();

        _actionList.push_back("PUSHBACK");
        _actionList.push_back("CROUCH_UP");

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
           if (_cnt % _sync.find(_strAction)->second.timing == 0)
           {
               _idx_x--;
               if (_idx_x < 1)
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
           if (_cnt % _sync.find(_strAction)->second.timing == 0)
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
           IMAGEMANAGER->findImage(_actionList.front())->setFrameY(_idx_y);
           if (_cnt % _sync.find(_actionList.front())->second.timing == 0)
           {
               _idx_x--;
               if (_idx_x < 1)
               {
                   _actionList.pop_front();
                   if (!_actionList.empty())
                   {
                       _idx_x = IMAGEMANAGER->findImage(_actionList.front())->getMaxFrameX();
                       if (!strcmp(_actionList.front(), "COUNTER"))
                           setState(ATTACK, true);
                       setAction(_actionList.front());
                   }
                   else
                   {
                       if (getState()[HIT] && _hit)
                           _hit = false;
                       _plState.reset();
                       _isFixed = _isAttack = _parrying = false;
                       setAction("IDLE");
                   }
               }

               if (!_actionList.empty())
                    IMAGEMANAGER->findImage(_actionList.front())->setFrameX(_idx_x);
               
           }
       }
       else
       {
           _idx_y = 0;
           IMAGEMANAGER->findImage(_actionList.front())->setFrameY(_idx_y);
           if (_cnt % _sync.find(_actionList.front())->second.timing == 0)
           {
               if (_idx_x > IMAGEMANAGER->findImage(_actionList.front())->getMaxFrameX())
               {
                   _actionList.pop_front();
                   if (!_actionList.empty())
                   {
                       _idx_x = 0;
                       if (!strcmp(_actionList.front(), "COUNTER"))
                           setState(ATTACK, true);
                       setAction(_actionList.front());
                   }
                   else
                   {
                       if (getState()[HIT] && _hit)
                           _hit = false;
                       _plState.reset();
                       _isFixed = _isAttack = _parrying = false;
                       _respawn = true;
                       setAction("IDLE");
                   }
               }
               if (!_actionList.empty())
                    IMAGEMANAGER->findImage(_actionList.front())->setFrameX(_idx_x);
               _idx_x++;
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
                if (_idx_x > getMaxFrameX() - 7)
                    _plPos.y -= 9.2f;
            }
            if (!strcmp(_strAction, "JUMP"))
            {
               if (_temp.y - _player.bottom < 200)
                    _plPos.y -= 9.5f;
                else
                {
                    setAction("FALLING");
                    setState(JUMP, false);
                }
            }
        }
        else
        {
            if (!strcmp(_strAction, "JUMP_FORWARD") && _idx_x < 7)
                _plPos.y -= 9.2f;
            if (!strcmp(_strAction, "JUMP"))
            {
                if (_temp.y - _player.bottom < 200)
                {
                    _plPos.y -= 9.5f;
                }
                else
                {
                    setAction("FALLING");
                    setState(JUMP, false);
                }
            }
        }
    }
    if (_plState[DODGE])
    {
        if (_isLeft)
        {
            _plPos.x -= 8.5f;
        }
        else
        {
            _plPos.x += 8.5f;
        }
    }
    if (_plState[ATTACK])
    {
        if (!strcmp(_actionList.front(), "ATTACK_DODGE"))
        {
            if (_isLeft)
            {
                if (_idx_x > getMaxFrameX() - 19 && _idx_x < getMaxFrameX() - 6)
                    _plPos.x -= 4.5f;
            }
            else
            {
                if (_idx_x < 19 && _idx_x > 6)
                    _plPos.x += 4.f;
            }
        }

    }

    if (!strcmp(_strAction, "PUSHBACK"))
    {
        if (_isLeft)
        {
            if (_idx_x > getMaxFrameX() - 9)
                _plPos.x += 5.0f;
        }
        else
        {
            if (_idx_x < 9)
                _plPos.x -= 5.0f;
        }
    }

    if (!strcmp(_strAction, "PARRY_SLIDE"))
    {
        if (_isLeft)
        {
            if (_idx_x > getMaxFrameX() - 7)
                _plPos.x += 7.0f;
        }
        else
        {
            if (_idx_x < 7)
                _plPos.x -= 7.0f;
        }
    }
}

int Player::getMaxFrameX()
{
    return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX();
}

Player::~Player()
{
}

void Player::comboAttack(void)
{
    if (_comboTime.empty())
    {
        setState(ATTACK, true);
        setAction("ATTACK");
        _actionList.push_back("ATTACK");

        if (_isLeft)
            _idx_x = IMAGEMANAGER->findImage("ATTACK")->getMaxFrameX();
        else
            _idx_x = 0;
    }
    else
    {
        if (_comboTime.back() - _attackTime.back() < 500)
        {
            if (!strcmp(_strAction, "ATTACK"))
            {
                //setState(ATTACK, true);
                setAction("ATTACK_COMBO_2");
                _actionList.push_back("ATTACK_COMBO_2");

            }
            else if (!strcmp(_strAction, "ATTACK_COMBO_2"))
            {

                //setState(ATTACK, true);
                setAction("ATTACK_COMBO_3");
                _actionList.push_back("ATTACK_COMBO_3");

            }
            else
            {
                //setState(ATTACK, true);
                setAction("ATTACK");
                _actionList.push_back("ATTACK");
                if (_isLeft)
                    _idx_x = IMAGEMANAGER->findImage("ATTACK")->getMaxFrameX();
                else
                    _idx_x = 0;
            }        
        }
        else
        {
        }
    }

}

void Player::renderPlayer(HDC hdc)
{
    if (_actionList.empty())
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _plPos.x + _sync.find(_strAction)->second.leftMove.x,
                _plPos.y + _sync.find(_strAction)->second.leftMove.y, _idx_x, _idx_y);

            _player = RectMake(_plPos.x + _sync.find(_strAction)->second.leftMove.x, 
                _plPos.y + _sync.find(_strAction)->second.leftMove.y,
                IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
        }
        else
        {
            IMAGEMANAGER->frameRender(_strAction, hdc,
                _plPos.x + _sync[_strAction].rightMove.x,
                _plPos.y + _sync[_strAction].rightMove.y, _idx_x, _idx_y);

            _player = RectMake(_plPos.x + _sync.find(_strAction)->second.rightMove.x,
                _plPos.y + _sync.find(_strAction)->second.rightMove.y,
                IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
                IMAGEMANAGER->findImage(_strAction)->getFrameHeight());
        }
    }
    else
    {
        if (_isLeft)
        {
            IMAGEMANAGER->frameRender(_actionList.front(), hdc, 
                _plPos.x + _sync.find(_actionList.front())->second.leftMove.x,
                _plPos.y + _sync.find(_actionList.front())->second.leftMove.y, _idx_x, _idx_y);

            _player = RectMake(_plPos.x + _sync.find(_actionList.front())->second.leftMove.x,
                _plPos.y + _sync.find(_actionList.front())->second.leftMove.y,
                IMAGEMANAGER->findImage(_actionList.front())->getFrameWidth(),
                IMAGEMANAGER->findImage(_actionList.front())->getFrameHeight());
            //cout << _sync.find(_actionList.front().c_str())->second.leftMove.y << endl;
        }
        else
        {
            IMAGEMANAGER->frameRender(_actionList.front(), hdc, 
                _plPos.x + _sync[_actionList.front()].rightMove.x,
                _plPos.y + _sync[_actionList.front()].rightMove.y, _idx_x, _idx_y);
            
            _player = RectMake(_plPos.x + _sync.find(_actionList.front())->second.rightMove.x,
                _plPos.y + _sync.find(_actionList.front())->second.rightMove.y,
                IMAGEMANAGER->findImage(_actionList.front())->getFrameWidth(),
                IMAGEMANAGER->findImage(_actionList.front())->getFrameHeight());
            //cout << _sync.find(_actionList.front().c_str())->second.rightMove.y << endl;
        }
    }
    
    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
        
        DrawRectMake(hdc, _hitBox);
        _stprintf_s(_loc, "x: %.2f y: %.2f", _plPos.x, _plPos.y);
        TextOut(hdc, _plPos.x, _plPos.y, _loc, strlen(_loc));
        TextOut(hdc, _plPos.x, _plPos.y + 20, _strAction, strlen(_strAction));

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}

void Player::renderProfile(HDC hdc)
{
    IMAGEMANAGER->render("Profile", hdc, 30, 30);
    IMAGEMANAGER->render("Score", hdc, WINSIZE_X - 200, 30);
    IMAGEMANAGER->render("HP", hdc, 186, 76, 0, 0, 
        IMAGEMANAGER->findImage("HP")->getWidth() * _hp / 100, IMAGEMANAGER->findImage("HP")->getHeight());

    for (int i = 0; i < 5; i++)
    {
        if (i < _portion)
        {
            IMAGEMANAGER->render("flask_full", hdc, 155 + 42 * i, 105);
        }
        else
        {
            IMAGEMANAGER->render("flask_empty", hdc, 155 + 42 * i, 105);
        }
    }
}