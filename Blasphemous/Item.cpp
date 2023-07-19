#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(int _posX, int _posY)
{
    IMAGEMANAGER->addFrameImage("Object", "Resources/Image/Sheet/object.bmp", 
        207 * 2, 182 * 2, 9, 2, true, MAGENTA);

    _pos = { _posX, _posY };
    _cnt = _obj = 0;
    _pick = false;


    return S_OK;
}

void Item::update(void)
{
    _object = RectMakeCenter(_pos.x, _pos.y, IMAGEMANAGER->findImage("Object")->getFrameWidth(),
        IMAGEMANAGER->findImage("Object")->getFrameHeight());

    _cnt++;
    if (_cnt % 5 == 0)
    {
        _obj++;
        if (_obj > 17)
        {
            _obj = 0;
        }

        _idx.x = _obj % 9;
        _idx.y = _obj / 9;

        IMAGEMANAGER->findImage("Object")->setFrameX(_idx.x);
        IMAGEMANAGER->findImage("Object")->setFrameY(_idx.y);
    }
}

void Item::showItem(HDC hdc)
{
    IMAGEMANAGER->frameRender("Object", hdc, _object.left, _object.top, _idx.x, _idx.y);

    if (_pick)
    {
        IMAGEMANAGER->render("KB_E", hdc,_object.left  + 10, _pos.y - 70);
    }

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

        DrawRectMake(hdc, _object);

        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
