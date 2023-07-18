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

    return S_OK;
}


void BossMap::render(HDC hdc)
{
    IMAGEMANAGER->render("BossMap_dark", hdc, 0, 0, 0, 0, WINSIZE_X, WINSIZE_Y);
}