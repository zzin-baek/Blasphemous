#include "Stdafx.h"
#include "Isidora.h"

HRESULT Isidora::init(void)
{
	IMAGEMANAGER->addFrameImage("Isidora_Intro", "Resources/Image/Isidora/Isidora_introSequence.bmp",
		2560 * 2, 1290 * 2, 10, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_idle", "Resoruces/Image/Isidora/Isidora_idleFinal.bmp",
		1484 * 2, 240 * 2, 14, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_vanish", "Resources/Image/Isidora/Isidora/idleToVanishFinal.bmp",
		1339 * 2, 254 * 2, 13, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_outToCast", "Resources/Image/Isidora/Isidora_outToCastFinal.bmp",
		1463 * 2, 260 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToRising", "Resources/Image/Isidora/Isidora_outToRisingScytheFinal.bmp",
		1944 * 2, 294 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToTwirl", "Resources/Image/Isidora/Isidora_outToTwirlFinal.bmp",
		1958 * 2, 262 * 2, 11, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_scy", "Resources/Image/Isidora/Isidora_risingScytheSequence.bmp",
		5516 * 2, 388 * 2, 28, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_slash", "Resources/Image/Isidora_slashSequence.bmp",
		8277 * 2, 338 * 2, 31, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_twirl", "Resources/Image/Isidora/Isidora_Twirl.bmp",
		1632 * 2, 256 * 2, 8, 2, true, MAGENTA);


	IMAGEMANAGER->addImage("Isidora_HP_Bar", "Resources/Image/Sheet/boss_healthBar.bmp",
		346 * 2, 30 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Isidora_HP", "Resources/Image/Sheet/boss_healthBlood.bmp", 
		289 * 2, 8 * 2, true, MAGENTA);
	_pos = { WINSIZE_X / 2 + 380, WINSIZE_Y / 2 - 400 };
	_cnt = _idx = _idx_x = _idx_y = 0;
	_hp = 200;

	_isLeft = true;
	_finIntro = false;
	wsprintf(_strSkill, "Isidora_Intro");

	return S_OK;
}

void Isidora::update(void)
{
	_cnt++;
	if (!_finIntro)
	{
		if (_cnt % 5 == 0)
		{
			if (_idx < 50)
			{
				_idx_x = _idx % (IMAGEMANAGER->findImage(_strSkill)->getMaxFrameX() + 1);
				_idx_y = _idx / (IMAGEMANAGER->findImage(_strSkill)->getMaxFrameX() + 1);

				IMAGEMANAGER->findImage(_strSkill)->setFrameX(_idx_x);
				IMAGEMANAGER->findImage(_strSkill)->setFrameY(_idx_y);

				//IMAGEMANAGER->frameRender(action, hdc, _pos.x, _pos.y, _idx_x, _idx_y);

				_idx++;
			}
			else
				_finIntro = true;
		}
	}
	else
	{

	}
}

void Isidora::routine(HDC hdc, int num, char* action, int maxFrame)
{
	if (num == 1)
	{
		if (_cnt % 5 == 0)
		{
			if (_idx < num)
			{
				_idx_x = _idx % (IMAGEMANAGER->findImage(action)->getMaxFrameX() + 1);
				_idx_y = _idx / (IMAGEMANAGER->findImage(action)->getMaxFrameX() + 1);

				IMAGEMANAGER->findImage(action)->setFrameX(_idx_x);
				IMAGEMANAGER->findImage(action)->setFrameY(_idx_y);

				IMAGEMANAGER->frameRender(action, hdc, _pos.x, _pos.y, _idx_x, _idx_y);

				_idx++;
			}
		}

	}
	else if (num == 2)
	{

		if (_isLeft)
		{
			_idx_y = 1;
			IMAGEMANAGER->findImage(action)->setFrameY(_idx_y);
			if (_cnt % 5 == 0)
			{
				_idx_x--;
				if (_idx_x > 0)
				{
					IMAGEMANAGER->findImage(action)->setFrameX(_idx_x);
					IMAGEMANAGER->frameRender(action, hdc, _pos.x, _pos.y, _idx_x, _idx_y);
						
				}

			}
		}
		else
		{
			_idx_y = 0;
			IMAGEMANAGER->findImage(action)->setFrameY(_idx_y);
			if (_cnt % 5 == 0)
			{
				_idx_x++;
				if (_idx_x <= IMAGEMANAGER->findImage(action)->getMaxFrameX())
				{
					IMAGEMANAGER->findImage(action)->setFrameX(_idx_x);
					render(hdc);
				}
					
					
			}
		}
	}
}

void Isidora::render(HDC hdc)
{
	IMAGEMANAGER->frameRender("Isidora_Intro", hdc, _pos.x, _pos.y, _idx_x, _idx_y);

	if (_hp > 0)
	{
		IMAGEMANAGER->render("Isidora_HP", hdc, 348, 680);
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 654);
		FONTMANAGER->drawText(hdc, 360, 632, "Neo둥근모 Pro", 30, 1, L"죽은 자들을 위해 노래하는 성녀 이시도라",
			0, RGB(171, 154, 63));
	}

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		//DrawRectMake(hdc, _);
		_stprintf_s(_loc, "x: %d y: %d", _pos.x, _pos.y);
		TextOut(hdc, _pos.x, _pos.y, _loc, strlen(_loc));
		
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}
}
