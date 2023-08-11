#include "Stdafx.h"
#include "BattleField.h"

HRESULT BattleField::init(void)
{
    IMAGEMANAGER->addImage("church-bg", "Resources/Image/BackGround/churches-field-map-bg.bmp",
        2000, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg", "Resources/Image/BackGround/churches-field-bg.bmp",
        2000, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg2", "Resources/Image/BackGround/churches-field-bg2.bmp",
        2000, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("churches-field-bg3", "Resources/Image/BackGround/churches-field-bg3.bmp",
        2000, WINSIZE_Y, true, MAGENTA);
    /*IMAGEMANAGER->addImage("church-field", "Resources/Image/BackGround/churches-field-map22(ladder).bmp",
        2000, 938, true, MAGENTA);
    IMAGEMANAGER->addImage("bg_collision", "Resources/Image/BackGround/churches-field-map_colision2.bmp",
        2000 , 938, true, RGB(255, 255, 255));*/
    IMAGEMANAGER->addImage("church-field", "Resources/Image/BackGround/churches_map_exp.bmp",
        3760, 940, true, MAGENTA);
    IMAGEMANAGER->addImage("bg_collision", "Resources/Image/BackGround/churches_map_exp_collision.bmp",
        3760, 940, true, RGB(255, 255, 255));

    IMAGEMANAGER->addImage("church-door", "Resources/Image/BackGround/churches_door.bmp",
        3760, 940, true, MAGENTA);
    
    _shake = { 0.0f, 0.0f };

    _startPos_x = 0.0f;
    _startPos_y = 70.0f;

    _copyPos_x = _startPos_x;
    _copyPos_y = _startPos_y;

    return S_OK;
}

void BattleField::rectMove(void)
{
    _ladder = RectMake(988 - (_startPos_x - _copyPos_x),
        245 - (_startPos_y - _copyPos_y), 30, 350);
}

void BattleField::cameraShake(void)
{
    int _dir = RND->getInt(8);

    switch (_dir)
    {
    case 0:
        _shake.x += 5;
        break;
    case 1:
        _shake.y += 5;
        break;
    case 2:
        _shake.x -= 5;
        break;
    case 3:
        _shake.y -= 5;
        break;
    case 4:
        _shake.x += 5;
        _shake.y += 5;
        break;
    case 5:
        _shake.x += 5;
        _shake.y -= 5;
        break;
    case 6:
        _shake.x -= 5;
        _shake.y += 5;
        break;
    case 7:
        _shake.x -= 5;
        _shake.y -= 5;
        break;
    }

    cout << "shake" << _shake.x << " " << _shake.y << endl;
}

void BattleField::renderDoor(HDC hdc)
{
    IMAGEMANAGER->render("church-door", hdc, 0, 0, _startPos_x, _startPos_y, WINSIZE_X, WINSIZE_Y);
}

void BattleField::render(HDC hdc)
{
    IMAGEMANAGER->render("church-bg", hdc, 0, -100);
    IMAGEMANAGER->render("churches-field-bg", hdc, 0, 100);
    IMAGEMANAGER->render("churches-field-bg3", hdc, 0, 50);
    IMAGEMANAGER->render("churches-field-bg2", hdc, 0, 50);
    
    IMAGEMANAGER->render("church-field", hdc, 0 + _shake.x, 0 + _shake.y, 
        _startPos_x, _startPos_y, WINSIZE_X, WINSIZE_Y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        //ÇÈ¼¿Ãæµ¹¿ë
        IMAGEMANAGER->render("bg_collision", hdc, 0, 0, _startPos_x, _startPos_y, WINSIZE_X, WINSIZE_Y);
        DrawRectMake(hdc, _ladder);

    }
}
