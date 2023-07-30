#include "Stdafx.h"
#include "Stoner.h"

HRESULT Stoner::init(void)
{
	IMAGEMANAGER->addFrameImage("Stoner_rising", "Resources/Image/Enemy/stoner_rising_anim.bmp",
		1034 * 2, 106 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_idle", "Resources/Iamge/Enemy/stoner_idle_anim.bmp",
		1128 * 2, 106 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_leftright", "Resources/Image/Enemy/stoner_leftright_anim.bmp",
		658 * 2, 106 * 2, 7, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_attack", "Resources/Image/Enemy/stoner_attack_anim.bmp",
		1960 * 2, 148 * 2, 20, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Stoner_death", "Resources/Iamge/Enemy/stoner_death_anim.bmp",
		1952 * 2, 162 * 2, 16, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Rock", "Resources/Image/Enemy/thrown_rock_anim.bmp",
		136 * 2, 68 * 2, 8, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Rock_landing", "Resources/Image/Enemy/rock_ground_landing_anim.bmp",
		441 * 2, 116 * 2, 7, 2, true, MAGENTA);


	return S_OK;
}

void Stoner::move(void)
{
}

void Stoner::render(HDC hdc)
{
}
