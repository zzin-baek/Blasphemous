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

    for (int i = 0; i < 10; i++)
    {
        _box[i] = RectMake(0 + 60 * i, 480, 60, 60);
    }
    for (int i = 0; i < 10; i++)
    {
        _box[i + 10] = RectMake(600 + 60 * i, 630, 60, 60);
    }

    return S_OK;
}

void BattleField::render(HDC hdc)
{
    IMAGEMANAGER->render("church-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg3", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg2", hdc, 0, 0);
    
    IMAGEMANAGER->render("church-field", hdc, 0, 0, WINSIZE_X, WINSIZE_Y, _startPos.x, _startPos.y, 680, 380);

    if (KEYMANAGER->isToggleKey('Z'))
    {
        for (int i = 0; i < 20; i++)
        {
            DrawRectMake(hdc, _box[i]);
        }
    }
}
