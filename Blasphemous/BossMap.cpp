#include "Stdafx.h"
#include "BossMap.h"

HRESULT BossMap::init(void)
{
    IMAGEMANAGER->addImage("BossMap_dark", "Resources/Image/BackGround/Isidora_map.bmp",
        1200 * 2, 360 * 2);
    IMAGEMANAGER->addImage("BossMap_bright", "Resources/Image/BackGround/Isidora_map_bright.bmp",
        640 * 2, 360 * 2);

    IMAGEMANAGER->addImage("BossMap_collision", "Resources/Image/BackGround/Isidora_map_collision.bmp",
        1200 * 2, 360 * 2);

    IMAGEMANAGER->addFrameImage("Brazier_dark", "Resources/Image/BackGround/Isidora_brazierHalfLoop_dark.bmp",
        700 * 2, 180 * 2, 7, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Brazier_HalfLoop", "Resources/Image/BackGround/Isidora_brazierHalfLoop.bmp",
        700 * 2, 180 * 2, 7, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Brazier_toHalf", "Resources/Image/BackGround/Isidora_braziertoHalf.bmp",
        600 * 2, 180 * 2, 6, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Brazier_HalfToFull", "Resources/Image/BackGround/Isidora_brazierHalfToFull.bmp",
        1700 * 2, 180 * 2, 17, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("Brazier_FullLoop", "Resources/Image/BackGround/Isidora_brazierFullLoop.bmp",
        1000 * 2, 180 * 2, 10, 1, true, MAGENTA);

    _pos = _idx = { 0, 0 };
    _cnt = _scene = 0;

    _sceneStart = RectMakeCenter(780, 580, 70, 120);
    wsprintf(_brazier, "Brazier_dark");

    return S_OK;
}

void BossMap::movdRect(int x)
{
    _sceneStart.left -= x;
    _sceneStart.right -= x;
}

void BossMap::update(void)
{
    _cnt++;
    if (_cnt % 8 == 0)
    {
        _idx.x++;
        if (_idx.x > IMAGEMANAGER->findImage(_brazier)->getMaxFrameX())
        {
            _idx.x = 0;
        }

        IMAGEMANAGER->findImage(_brazier)->setFrameX(_idx.x);
        IMAGEMANAGER->findImage(_brazier)->setFrameY(_idx.y);
    }
}


void BossMap::render(HDC hdc)
{
    IMAGEMANAGER->render("BossMap_dark", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->render("BossMap_bright", hdc, WINSIZE_X / 2 - _scene, 0,
        WINSIZE_X/2 - _scene, 0, + (_scene * 2), WINSIZE_Y);
    IMAGEMANAGER->frameRender(_brazier, hdc, 1185 - _pos.x, 270 - _pos.y, _idx.x, _idx.y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        IMAGEMANAGER->render("BossMap_collision", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);
        IMAGEMANAGER->render("BossMap_bright", hdc, 0, 0, 0, 0, WINSIZE_X, WINSIZE_Y);
        DrawRectMake(hdc, _sceneStart);
    }
}