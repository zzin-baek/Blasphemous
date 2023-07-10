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
    IMAGEMANAGER->addFrameImage("ATTACK_JUMP", "Resources/Image/Penitent/penitent_jumping_attack_noslash.bmp",
        850 * 2, 188 * 2, 10, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("COMBO_ATTACK", "Resources/Image/Penitent/penitent_three_hits_combo.bmp",
        6132 * 2, 154 * 2, 28, 2, true, MAGENTA);

    _plPos_x = WINSIZE_X / 2;
    _plPos_y = WINSIZE_Y / 2 + 50;
    _cnt = _idx_x = _idx_y = 0;
    _isLeft = false;

    for (int i = 0; i < MAX_STATE; i++)
    {
        setState(i, false);
    }

    wsprintf(_strAction, "IDLE");

    return S_OK;
}

void Player::playerAction(void)
{
    if (KEYMANAGER->isStayKeyDown('A'))
    {
        _isLeft = true;
        setState(WALK, true);
        if (!_plState[JUMP])
            setAction("RUNNING");
        if (_plPos_x > 0)
            _plPos_x -= 5.0f;
    }
    if (KEYMANAGER->isStayKeyDown('D') && _plPos_x < WINSIZE_X)
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
        if (_plState.none())
            setAction("CROUCH_DOWN");
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        _plState.reset();
        setAction("IDLE");
    }

    if (KEYMANAGER->isOnceKeyUp('S'))
    {
        setAction("CROUCH_UP");
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_plState[WALK] || _plState[DODGE])
        {
            setState(JUMP, true);
            setAction("JUMP_FORWARD");
        }
        else if (_plState.none())
        {
            setState(JUMP, true);
            setAction("JUMP");
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
    {
        setState(DODGE, true);
        setAction("DODGE");
    }
    if (KEYMANAGER->isOnceKeyDown('K'))
    {
        setAction("COMBO_ATTACK");
    }

   _cnt++;
    if (_isLeft)
    {
        _idx_y = 1;
        IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
        if (_cnt % 5 == 0)
        {            
            _idx_x--;
            if (_idx_x < 0)
            {
                _idx_x = IMAGEMANAGER->findImage(_strAction)->getMaxFrameX();
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
            if (_idx_x > IMAGEMANAGER->findImage(_strAction)->getMaxFrameX())
            {
                _idx_x = 0;
            }
            IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx_x);
        }
    }
}

Player::~Player()
{
    
}

void Player::renderPlayer(HDC hdc)
{
    IMAGEMANAGER->frameRender(_strAction, hdc, _plPos_x, _plPos_y, _idx_x, _idx_y);
}