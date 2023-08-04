#include "Stdafx.h"
#include "Pietat.h"

HRESULT Pietat::init(void)
{
	IMAGEMANAGER->addFrameImage("Pietat_appear", "Resources/Image/Pietat/pietat_appear.bmp",
		5654 * 2, 2280 * 2, 11, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_death", "Resources/Image/Pietat/pietat_death.bmp",
		9620 * 2, 410 * 2, 37, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Pietat_idle", "Resources/Image/Pietat/pietat_idle_anim.bmp",
		1846 * 2, 454 * 2, 13, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_walk", "Resources/Image/Pietat/pietat_walk.bmp",
		2576 * 2, 464 * 2, 16, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_walkToIdle", "Resources/Image/Pietat/pietat_walkToIdle.bmp",
		1720 * 2, 462 * 2, 10, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_turnaround", "Resources/Image/Pietat/pietat_turnaround.bmp",
		1898 * 2, 456 * 2, 13, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Pietat_smash", "Resources/Image/Pietat/pietat_ground_smash_anim.bmp",
		15047 * 2, 530 * 2, 41, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_smashToIdle", "Resources/Image/Pietat/pietat_ground_smashToIdle_anim.bmp",
		1431 * 2, 436 * 2, 9, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_smashToIdle_reverse", "Resources/Image/Pietat/pietat_ground_smash_reverseToIdle_anim.bmp",
		1611 * 2, 436 * 2, 9, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Pietat_slash", "Resources/Image/Pietat/pietat_slash_anim.bmp",
		17784 * 2, 456 * 2, 52, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Pietat_spit_start", "Resources/Image/Pietat/pietat_spit_start_anim.bmp",
		1420 * 2, 456 * 2, 10, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_spit", "Resources/Image/Pietat/pietat_spit_loop_anim.bmp",
		2130 * 2, 448 * 2, 15, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_spitToIdle", "Resources/Image/Pietat/pietat_spit_backToIdle.bmp",
		710 * 2, 456 * 2, 5, 2, true, MAGENTA);
	
	IMAGEMANAGER->addFrameImage("Pietat_stomp", "Resources/Image/Pietat/pietat_stomp_anim.bmp",
		4541 * 2, 446 * 2, 19, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_step1ToIdle", "Resources/Image/Pietat/pietat_step1ToIdle.bmp",
		1557 * 2, 460 * 2, 9, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Pietat_step2ToIdle", "Resources/Image/Pietat/pietat_step2ToIdle.bmp",
		710 * 2, 450 * 2, 5, 2, true, MAGENTA);

	// projectile
	IMAGEMANAGER->addFrameImage("Thorn", "Resources/Image/Pietat/thorn_projectile_anim.bmp",
		250 * 2, 26 * 2, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_destroy", "Resources/Image/Pietat/thorn_projectile_destroyed_anim.bmp",
		658 * 2, 48 * 2, 14, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_unravel", "Resources/Image/Pietat/thorn_projectile_unraveling_anim.bmp",
		1408 * 2, 45 * 2, 22, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_unravel_destroy", "Resources/Image/Pietat/thorn_projectile_unraveled_destroyed_anim.bmp",
		2508 * 2, 120 * 2, 22, 1, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Thorn_tower", "Resources/Image/Pietat/thorns_tower_anim.bmp",
		640 * 2, 504 * 2, 10, 4, true, MAGENTA);

	return S_OK;
}

void Pietat::initSync(void)
{
}

void Pietat::update(void)
{
}

void Pietat::useSkill(void)
{
}

void Pietat::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		DrawRectMake(hdc, _hitBox);

		_stprintf_s(_loc, "x: %.2f y: %.2f", _pos.x, _pos.y);
		TextOut(hdc, _pos.x, _pos.y, _loc, strlen(_loc));

		myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		oldPen = (HPEN)SelectObject(hdc, myPen);


		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}
}
