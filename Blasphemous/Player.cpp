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
    IMAGEMANAGER->addFrameImage("JUMP_FOWARD", "Resources/Image/Penitent/penitent_jump_forward_anim.bmp",
        1230 * 2, 164 * 2, 15, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("HANGON", "Resources/Image/Penitent/penitent_hangonledge_anim.bmp",
        1872 * 2, 166 * 2, 18, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("CLIMB", "Resources/Image/Penitent/penitent_climbledge_reviewed.bmp",
        1020 * 2, 262 * 2, 10, 2, true, MAGENTA);

    _plPos_x = WINSIZE_X / 2;
    _plPos_y = WINSIZE_Y / 2 + 50;
    _cnt = _idx_x = _idx_y = 0;
    _isLeft = false;

    _plState.set();

    wsprintf(_strAction, "IDLE");

    return S_OK;
}

void Player::playerAction(void)
{
    if (KEYMANAGER->isStayKeyDown('A'))
    {
        _isLeft = true;
        wsprintf(_strAction, "RUNNING");
        _plPos.x -= 5;
    }
    if (KEYMANAGER->isStayKeyDown('D'))
    {
        _isLeft = false;
        wsprintf(_strAction, "RUNNING");
        _plPos.x += 5;
    }
    if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
    {
        wsprintf(_strAction, "IDLE");
    }

    _cnt++;
    if (_isLeft)
    {
        IMAGEMANAGER->findImage(_strAction)->setFrameY(1);
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
        IMAGEMANAGER->findImage(_strAction)->setFrameY(0);
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
    /*IMAGEMANAGER->frameRender(_strAction, hdc, _plPos.x, _plPos.y,
        IMAGEMANAGER->findImage(_strAction)->getFrameX(),
        IMAGEMANAGER->findImage(_strAction)->getFrameY());*/
    IMAGEMANAGER->frameRender(_strAction, hdc, _plPos_x, _plPos_y, _idx_x, _idx_y);
}