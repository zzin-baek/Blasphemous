#include "Stdafx.h"
#include "BossMap2.h"

HRESULT BossMap2::init(void)
{
	IMAGEMANAGER->addImage("Piedad_map", "Resources/Image/BackGround/piedad_map.bmp",
		2000 * 2, 360 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Piedad_bg1", "Resources/Image/BackGround/piedad_bg1.bmp",
		900 * 2, WINSIZE_Y, true, MAGENTA);
	IMAGEMANAGER->addImage("Piedad_bg2", "Resources/Image/BackGround/piedad_bg2.bmp",
		1000 * 2, WINSIZE_Y, true, MAGENTA);
	IMAGEMANAGER->addImage("Piedad_bg3", "Resources/Image/BackGround/piedad_bg3.bmp",
		2000 * 2, 429 * 2, true, MAGENTA);

	IMAGEMANAGER->addImage("Piedad_map_collision", "Resources/Image/BackGround/piedad_map_collision.bmp",
		2000 * 2, 360 * 2, true, RGB(255, 255, 255));

	_pos = { 4000 - WINSIZE_X, 0 };

	return S_OK;
}

void BossMap2::render(HDC hdc)
{
	IMAGEMANAGER->render("Piedad_bg1", hdc, 0, 0);
	IMAGEMANAGER->render("Piedad_bg2", hdc, 0, 0);
	IMAGEMANAGER->render("Piedad_map", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->render("Piedad_map_collision", hdc, 0, 0,
			_pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);
	}
}

void BossMap2::renderColumn(HDC hdc)
{
	IMAGEMANAGER->render("Piedad_bg3", hdc, 0, 0, _pos.x, _pos.y, WINSIZE_X, WINSIZE_Y);
}
