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
        WINSIZE_X, WINSIZE_Y, true, MAGENTA);
    
    _startPos = { 0, 0 };
    for (int i = 0; i < 10; i++)
    {
        _box[i] = RectMake(0 + 50 * i, 450, 50, 50);
    }
    for (int i = 0; i < 10; i++)
    {
        _box[i + 10] = RectMake(500 + 50 * i, 560, 50, 50);
    }

    return S_OK;
}

void BattleField::movePlayer()
{
 
}

void BattleField::render(HDC hdc)
{
    IMAGEMANAGER->render("church-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg3", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg2", hdc, 0, 0);
    
    IMAGEMANAGER->render("church-field", hdc, 0, 0, WINSIZE_X, WINSIZE_Y, 0, 100, 850, 500);

    if (KEYMANAGER->isToggleKey('Z'))
    {
        for (int i = 0; i < 20; i++)
        {
            DrawRectMake(hdc, _box[i]);
        }
    }
}
