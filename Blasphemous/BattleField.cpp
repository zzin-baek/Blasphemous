#include "Stdafx.h"
#include "BattleField.h"

HRESULT BattleField::init(void)
{
    IMAGEMANAGER->addImage("church-bg", "Resources/Image/BackGround/churches-field-map-bg.bmp",
        WINSIZE_X, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg", "Resources/Image/BackGround/churches-field-bg.bmp",
        WINSIZE_X, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg2", "Resources/Image/BackGround/churches-field-bg2.bmp",
        1300, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg3", "Resources/Image/BackGround/churches-field-bg3.bmp",
        1016, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("church-field", "Resources/Image/BackGround/churches-field-map.bmp",
        1280, 600, true, MAGENTA);
    
    _startPos = { 0, 70 };

    _box[0] = RectMake(0, 525, 650, 60);
    _box[1] = RectMake(650, 650, 700, 60);
    return S_OK;
}

void BattleField::render(HDC hdc)
{
    IMAGEMANAGER->render("church-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg3", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg2", hdc, 0, 0);
    
    IMAGEMANAGER->render("church-field", hdc, 0, 0, WINSIZE_X, WINSIZE_Y, _startPos.x, _startPos.y, 680, 380);

    if (KEYMANAGER->isToggleKey(VK_CONTROL))
    {
        HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
        HPEN myPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
        
        for (int i = 0; i < 2; i++)
        {
            DrawRectMake(hdc, _box[i]);
        }
        
        SelectObject(hdc, oldBrush);
        DeleteObject(myBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(myPen);
    }
}
