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

    _acolytePos = { WINSIZE_X / 2, WINSIZE_Y / 2 + 205 };
    _isLeft = false;
    _cnt = _idx_x = _idx_y = 0;
    _acState.reset();
    setState(IDLE_ENEMY, true);

    wsprintf(_strAction, "Acolyte_idle");

    return S_OK;
}

void Acolyte::move(void)
{
    _acolyte = RectMake(_acolytePos.x, _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight(),
        IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
        IMAGEMANAGER->findImage(_strAction)->getFrameHeight());

    _attackBoundary[0] = RectMake(_acolytePos.x - 200, _acolytePos.y - 80,
        200, 80);
    _attackBoundary[1] = RectMake(_acolytePos.x + IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
        _acolytePos.y - 80, 200, 80);

    if (_isLeft && _acState[IDLE_ENEMY])
    {
        _acolytePos.x -= 1;
    }
    else if (!_isLeft && _acState[IDLE_ENEMY])
    {
        _acolytePos.x += 1;
    }
    _cnt++;
    if (_isLeft)
    {
        _idx_y = 1;
        IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx_y);
        if (_cnt % 8 == 0)
        {
            _idx_x--;
            if (_idx_x < 0)
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
        if (_cnt % 8 == 0)
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

void Acolyte::render(HDC hdc)
{
    IMAGEMANAGER->frameRender(_strAction, hdc,
        _acolytePos.x, _acolytePos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight(),
        _idx_x, _idx_y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _acolyte);
        
        _stprintf_s(_loc, "x: %d y: %d", _acolytePos.x, _acolytePos.y);
        TextOut(hdc, _acolytePos.x + 50, _acolytePos.y - 20, _loc, strlen(_loc));
        
        
        myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _attackBoundary[0]);
        DrawRectMake(hdc, _attackBoundary[1]);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
