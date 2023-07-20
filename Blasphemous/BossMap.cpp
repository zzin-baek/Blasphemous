#include "Stdafx.h"
#include "BossMap.h"

HRESULT BossMap::init(void)
{
    IMAGEMANAGER->addImage("BossMap_dark", "Resources/Image/BackGround/Isidora_map.bmp",
        1200 * 2, 360 * 2);
    IMAGEMANAGER->addImage("BossMap_bright", "Resources/Image/BackGround/Isidora_map_bright",
        640 * 2, 360 * 2);

    IMAGEMANAGER->addImage("BossMap_collision", "Resources/Image/BackGround/Isidora_map_collision.bmp",
        1200 * 2, 360 * 2);

    IMAGEMANAGER->addFrameImage("Brazier_Loop", "Resources/Image/Isidora/Isidora_brazierHalfLoop_dark.bmp",
        300 * 2, 540 * 2, 3, 3, true, MAGENTA);

    _pos = { 0, 0 };
    _sceneStart = RectMakeCenter(780, 580, 70, 120);

    return S_OK;
}

void BossMap::movdRect(int x)
{
    _sceneStart.left -= x;
    _sceneStart.right -= x;
}


void BossMap::render(HDC hdc)
{
    IMAGEMANAGER->render("BossMap_dark", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        IMAGEMANAGER->render("BossMap_collision", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);
        DrawRectMake(hdc, _sceneStart);
    }
}