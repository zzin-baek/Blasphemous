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
    IMAGEMANAGER->addImage("church-field", "Resources/Image/BackGround/churches-field-map2.bmp",
        2000, 938, true, MAGENTA);
    IMAGEMANAGER->addImage("bg_collision", "Resources/Image/BackGround/churches-field-map_colision2.bmp",
        2000 , 938, true, RGB(255, 255, 255));
    
    _startPos_x = 0.0f;
    _startPos_y = 70.0f;

    _startPos = { 0, 70 };
    return S_OK;
}

void BattleField::render(HDC hdc)
{
    IMAGEMANAGER->render("church-bg", hdc, 0, -100);
    IMAGEMANAGER->render("churches-field-bg", hdc, 0, 100);
    IMAGEMANAGER->render("churches-field-bg3", hdc, 0, 0);
    IMAGEMANAGER->render("churches-field-bg2", hdc, 0, 0);
    
    IMAGEMANAGER->render("church-field", hdc, 0, 0, _startPos_x, _startPos_y, WINSIZE_X, WINSIZE_Y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        //ÇÈ¼¿Ãæµ¹¿ë
        IMAGEMANAGER->render("bg_collision", hdc, 0, 0, _startPos_x, _startPos_y, WINSIZE_X, WINSIZE_Y);

    }
}
