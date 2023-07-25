#include "Stdafx.h"
#include "Isidora.h"

HRESULT Isidora::init(void)
{
	IMAGEMANAGER->addFrameImage("Isidora_Intro", "Resources/Image/Isidora/Isidora_introSequence.bmp",
		2560 * 2, 1290 * 2, 10, 5, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_Intro2", "Resources/Image/Isidora/Isidora_introSequence2.bmp",
		12800 * 2, 516 * 2, 50, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_idle", "Resources/Image/Isidora/Isidora_idleFinal.bmp",
		1484 * 2, 240 * 2, 14, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_vanish", "Resources/Image/Isidora/Isidora_idleToVanishFinal.bmp",
		1339 * 2, 254 * 2, 13, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_outToCast", "Resources/Image/Isidora/Isidora_outToCastFinal.bmp",
		1463 * 2, 260 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToRising", "Resources/Image/Isidora/Isidora_outToRisingScytheFinal.bmp",
		1944 * 2, 294 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToTwirl", "Resources/Image/Isidora/Isidora_outToTwirlFinal.bmp",
		1958 * 2, 262 * 2, 11, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_scy", "Resources/Image/Isidora/Isidora_risingScytheSequence.bmp",
		5516 * 2, 388 * 2, 28, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_scy2", "Resources/Image/Isidora/Isidora_risingScySequence2.bmp",
		6534 * 2, 432 * 2, 27, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_scy_crop", "Resources/Image/Isidora/Isidora_risingScySequence_crop.bmp",
		1694 * 2, 432 * 2, 7, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_slash", "Resources/Image/Isidora/Isidora_slashSequence.bmp",
		8277 * 2, 338 * 2, 31, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_screen_slash", "Resources/Image/Isidora/Isidora-screenslash.bmp",
		744 * 2, 310 * 2, 4, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_twirl", "Resources/Image/Isidora/Isidora_Twirl.bmp",
		1632 * 2, 256 * 2, 8, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_cast", "Resources/Image/Isidora/Isidora_castSequenceFinal.bmp",
		4350 * 2, 240 * 2, 30, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_attackPattern", "Resources/Image/Isidora/Isidora_attackPattern.bmp",
		14280 * 2, 512 * 2, 42, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_twirlToVanish", "Resources/Image/Isidora/Isidora_twirlToVanishFinal.bmp",
		2424 * 2, 268 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_slashToVanish", "Resources/Image/Isidora/Isidora-screenslash_vanish.bmp",
		1872 * 2, 200 * 2, 12, 2, true, MAGENTA);

	// ºÒ±âµÕ
	IMAGEMANAGER->addFrameImage("Column_create", "Resources/Image/Isidora/FireColumnAnticipation.bmp",
		410 * 2, 1300 * 2, 5, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_create2", "Resources/Image/Isidora/FireColumnAnticipation2.bmp",
		1394 * 2, 325 * 2, 17, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_loop", "Resources/Image/Isidora/FireColumnLoop.bmp",
		328 * 2, 975 * 2, 4, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_out", "Resources/Image/Isidora/FireColumnOut.bmp",
		328 * 2, 1300 * 2, 4, 4, true, MAGENTA);

	// ºÒ¶Ë
	IMAGEMANAGER->addFrameImage("FireBall_create", "Resources/Image/Isidora/IsidoraProjectileIn.bmp",
		507 * 2, 39 * 2, 13, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("FireBall_loop", "Resources/Image/Isidora/IsidoraProjectileLoop.bmp",
		507 * 2, 39 * 2, 12, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("FireBall_out", "Resources/Image/Isidora/IsidoraProjectileOut.bmp",
		507 * 2, 39 * 2, 13, 1, true, MAGENTA);

	IMAGEMANAGER->addImage("Circle_Mask", "Resources/Image/Sheet/Circle_Mask.bmp",
		256, 256, true, MAGENTA);
	IMAGEMANAGER->addImage("Column_Mask", "Resources/Image/Sheet/Column_Mask.bmp", 
		200, 680, true, MAGENTA); // 300, 1024
	IMAGEMANAGER->addImage("Isidora_HP_Bar", "Resources/Image/Sheet/boss_healthBar.bmp",
		346 * 2, 30 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Isidora_HP", "Resources/Image/Sheet/boss_healthBlood.bmp", 
		289 * 2, 8 * 2, true, MAGENTA);
	
	_pos = { WINSIZE_X / 2 + 380, WINSIZE_Y / 2 - 100};
	_idx = { 0, 0 };
	_cnt = _patternNum = 0;
	_interval = 10;
	_test = { 1100.0f, 450.0f };

	_hp = 200;

	_isLeft = true;
	_finIntro = _once = false;
	
	tempX = 500.0f; 
	tempY = 450.0f;
	
	initSync();

	return S_OK;
}

void Isidora::initSync(void)
{
	_sync.insert({ "Isidora_Intro", { 7, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_Intro2", { 6, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_idle", { 7, {-12, 18}, {0, 0} } });
	_sync.insert({ "Isidora_vanish", { 7, {-10, 10}, {0, 0} } });
	_sync.insert({ "Isidora_outToCast", { 7, {-50, 20}, {0, 0} } });
	_sync.insert({ "Isidora_outToRising", { 10, {20, 30}, {0, 30} } });
	_sync.insert({ "Isidora_outToTwirl", { 7, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_scy", { 7, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_scy2", { 7, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_scy_crop", {10, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_slash", { 8, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_screen_slash", { 10, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_twirl", { 8, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_attackPattern", { 5, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_twirlToVanish", { 8, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_slashToVanish", { 8, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_cast", { 8, {0, 0}, {0, 0} } });
}

void Isidora::update(void)
{
	_plPos = { PLAYER->getCenterX(), PLAYER->getCenterY() };
	_box = RectMakeCenter(_test.x, _test.y, 50, 50);

	_cnt++;
	if (!_pattern.empty())
	{
		if (_isLeft)
		{
			_idx.y = 1;
			IMAGEMANAGER->findImage(_pattern.front())->setFrameY(_idx.y);
			if (_cnt % _sync.find(_pattern.front())->second.timing == 0)
			{
				_idx.x--; 
				if (_idx.x < 1)
				{
					_pattern.pop_front();
					if (!_pattern.empty())
					{
						_idx.x = IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX();
					}
					else
					{
						if (!_finIntro) _finIntro = true;

						_doNothing = true;
					}
				}
				if (!_pattern.empty())
					IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx.x);
			}
		}
		else
		{
			_idx.y = 0;
			IMAGEMANAGER->findImage(_pattern.front())->setFrameY(_idx.y);
			if (_cnt % _sync.find(_pattern.front())->second.timing == 0)
			{
				_idx.x++;
				if (_idx.x > IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX())
				{
					_pattern.pop_front();
					if (!_pattern.empty())
					{
						_idx.x = 0;
					}
					else
					{
						if (!_finIntro) _finIntro = true;

						_doNothing = true;
					}
				}
				if (!_pattern.empty())
					IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx.x);
			}
		}
	}
	useSkill();

	if (_cnt % _interval == 0)
	{
		columnCreate();
		fireBallCreate();
	}

	columnCycle();

	fireBallMove();
	fireBallCycle();

}

void Isidora::useSkill(void)
{
	RECT _rt;
	bool _fine = false;
	/*if (_finIntro)
	{
		if (_cnt % 2 == 0)
		{
			_test.x -= 6.0f;
			if (IntersectRect(&_rt, &PLAYER->getRect(), &_box) && !_fine)
			{
				tempX = PLAYER->getCenterX();
				_fine = true;
			}
			if (_test.x <= tempX)
			{
				_test.y = tempY - pow(5, (tempX - _test.x) / 30);
			}
			
			if (_test.y <= 100)
			{
				_test = { 1100, 450 };
				tempX = 500;
			}

			_pos = _test;
		}
	}*/
	switch (_patternNum)
	{
	case 1:
		if (!_once)
		{
			_interval = 30;
			for (int i = 0; i < 5; i++)
			{
				_cl[i]._clPos = { float((WINSIZE_X / (5 * 2)) + (WINSIZE_X / 5) * i), 0 };
				_cl[i]._idx = { 0, 0 };
				_cl[i]._create = true;
			}
			_once = true;
		}
		break;
	case 2:
		if (!_once)
		{
			_interval = 1;
			for (int i = 0; i < 3; i++)
			{
				_cl[i]._clPos = { float(WINSIZE_X / 2 - 180 + (180 * i)), 0 };
				_cl[i]._idx = { 0, 0 };
				_cl[i]._create = true;
			}
			_once = true;
		}
		break;
	case 3:
		if (!_once)
		{
			_interval = 100;
			for (int i = 0; i < 4; i++)
			{
				_fb[i]._center = { WINSIZE_X / 2 - 30, WINSIZE_Y / 2 };
				_fb[i]._idx = { 0, 0 };
				_fb[i]._cnt = 0;

				_fb[i]._angle = 90.0f;
				_fb[i]._create = true;
			}
			_once = true;
		}
		break;
	case 4:
		break;
	}


}

void Isidora::columnCreate(void)
{
	for (int i = 0; i < 7; i++)
	{
		if (_cl[i]._create && !_cl[i]._fire)
		{
			_cl[i]._fire = true;
			_cl[i]._cycle.push_back("Column_create2");
			_cl[i]._cycle.push_back("Column_loop");
			_cl[i]._cycle.push_back("Column_loop");
			_cl[i]._cycle.push_back("Column_out");

			break;
		}
	}
}

void Isidora::columnCycle(void)
{
	for (int i = 0; i < 7; i++)
	{
		if (_cl[i]._fire && !_cl[i]._cycle.empty() && _cnt % 3 == 0)
		{
			_cl[i]._cnt++;

			_cl[i]._idx.x = _cl[i]._cnt % (IMAGEMANAGER->findImage(_cl[i]._cycle.front())->getMaxFrameX() + 1);
			_cl[i]._idx.y = _cl[i]._cnt / (IMAGEMANAGER->findImage(_cl[i]._cycle.front())->getMaxFrameX() + 1);

			if (_cl[i]._cnt > (IMAGEMANAGER->findImage(_cl[i]._cycle.front())->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(_cl[i]._cycle.front())->getMaxFrameY() + 1) - 1)
			{
				_cl[i]._cnt = 0;
				_cl[i]._cycle.pop_front();
			}

			if (!_cl[i]._cycle.empty())
			{
				IMAGEMANAGER->findImage(_cl[i]._cycle.front())->setFrameX(_cl[i]._idx.x);
				IMAGEMANAGER->findImage(_cl[i]._cycle.front())->setFrameY(_cl[i]._idx.y);
			}
			else
			{
				_cl[i]._fire = false;
				_cl[i]._create = false;
				_cl[i]._clPos = { 0, 0 };
				if ((_patternNum == 1 && i == 4) || (_patternNum == 2 && i == 2) || (i == 6))
				{
					_once = false;
					_doNothing = true;
				}
			}
		}
	}
}

void Isidora::fireBallCreate(void)
{
	for (int i = 0; i < 10; i++)
	{
		if (_fb[i]._create && !_fb[i]._fire)
		{
			_fb[i]._fire = true;
			_fb[i]._cycle.push_back("FireBall_create");
			_fb[i]._cycle.push_back("FireBall_loop");

			break;
		}
	}
}

void Isidora::fireBallMove(void)
{
	POINTF center;
	float ag;

	if (_cnt % 3 == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			if (_fb[i]._fire)
			{
				if (_fb[i]._angle < 230)
				{
					center.x = _fb[i]._center.x + 3 * cos((_fb[i]._angle + 2) * PI / 180);
					center.y = _fb[i]._center.y - 3 * sin((_fb[i]._angle + 2) * PI / 180);

					_fb[i]._center = { center.x, center.y };
					_fb[i]._angle += 2;
				}
				else
				{
					ag = atan2((PLAYER->getCenterY() - _fb[i]._center.y),
						(_fb[i]._center.x - PLAYER->getCenterX()));

					cout << "ag" << ag * 180 / PI << endl;

					center.x = _fb[i]._center.x + 3 * cos((ag - (180 * PI / 180)));
					center.y = _fb[i]._center.y - 3 * sin((ag - (180 * PI / 180)));

					_fb[i]._center = { center.x, center.y };
					_fb[i]._angle = ag * (180 / PI);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (_fb[i]._fire)
			{
				center.x = _fb[i]._center.x + 3 * cos((_fb[i]._angle * PI / 180));
				center.y = _fb[i]._center.y - 3 * sin((_fb[i]._angle * PI / 180));

				_fb[i]._center = { center.x, center.y };

				//cout << "angle" << _fb[i]._angle << endl;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (_fb[i]._fire)
		{
			if (PtInRect(&PLAYER->getRect(), { int(_fb[i]._center.x), int(_fb[i]._center.y) }))
				_fb[i]._visible = false;
			else if (_fb[i]._center.y > 600 || _fb[i]._center.y < -30)
				_fb[i]._visible = false;
		}
	}
	//cout << _fb[0]._angle << endl;
}

void Isidora::fireBallCycle(void)
{
	for (int i = 0; i < 7; i++)
	{
		if (_fb[i]._fire && !_fb[i]._cycle.empty() && _cnt % 3 == 0)
		{
			_fb[i]._cnt++;

			_fb[i]._idx.x = _fb[i]._cnt % (IMAGEMANAGER->findImage(_fb[i]._cycle.front())->getMaxFrameX() + 1);

			if (_fb[i]._cnt > (IMAGEMANAGER->findImage(_fb[i]._cycle.front())->getMaxFrameX() + 1) - 1)
			{
				_fb[i]._cnt = 0;
				if (!strcmp(_fb[i]._cycle.front(), "FireBall_out"))
				{
					_fb[i]._fire = false;
					_fb[i]._create = false;
					_fb[i]._center = { WINSIZE_X / 2, WINSIZE_Y / 2 };
					_fb[i]._visible = true;

					if (i == 3)
					{
						_once = false;
						_doNothing = true;
					}
				}
				_fb[i]._cycle.pop_front();
			}

			if (!_fb[i]._cycle.empty())
			{
				IMAGEMANAGER->findImage(_fb[i]._cycle.front())->setFrameX(_fb[i]._idx.x);
				IMAGEMANAGER->findImage(_fb[i]._cycle.front())->setFrameY(_fb[i]._idx.y);
			}
			else
			{
				if (_fb[i]._fire)
				{
					if (_fb[i]._visible)
						_fb[i]._cycle.push_back("FireBall_loop");

					else
						_fb[i]._cycle.push_back("FireBall_out");
				}
			}
		}
	}
}

void Isidora::render(HDC hdc)
{
	if (!_pattern.empty())
	{
		_isidora = RectMakeCenter(_pos.x, _pos.y,
			IMAGEMANAGER->findImage(_pattern.front())->getFrameWidth(),
			IMAGEMANAGER->findImage(_pattern.front())->getFrameHeight());
		if (_isLeft)
		{
			IMAGEMANAGER->frameRender(_pattern.front(), hdc,
				_isidora.left + _sync[_pattern.front()].left.x, 
				_isidora.top + _sync[_pattern.front()].left.y, _idx.x, _idx.y);
		}
		else
		{
			IMAGEMANAGER->frameRender(_pattern.front(), hdc,
				_isidora.left + _sync[_pattern.front()].right.x,
				_isidora.top + _sync[_pattern.front()].right.y, _idx.x, _idx.y);
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (_cl[i]._fire && !_cl[i]._cycle.empty())
		{
			_mask = RectMake(_cl[i]._clPos.x - 100, _cl[i]._clPos.y, 164, 650);
			IMAGEMANAGER->alphaRender("Column_Mask", hdc, _mask.left, _mask.top, 30);
			IMAGEMANAGER->frameRender(_cl[i]._cycle.front(), hdc, 
				_cl[i]._clPos.x - 82, _cl[i]._clPos.y, _cl[i]._idx.x, _cl[i]._idx.y);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (_fb[i]._fire && !_fb[i]._cycle.empty())
		{
			IMAGEMANAGER->frameRender(_fb[i]._cycle.front(), hdc,
				_fb[i]._center.x, _fb[i]._center.y, _fb[i]._idx.x, _fb[i]._idx.y);
		}
	}

	if (_hp > 0)
	{
		IMAGEMANAGER->render("Isidora_HP", hdc, 348, 680);
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 654);
		FONTMANAGER->drawText(hdc, 360, 632, "NeoµÕ±Ù¸ð Pro", 30, 1, L"Á×Àº ÀÚµéÀ» À§ÇØ ³ë·¡ÇÏ´Â ¼º³à ÀÌ½Ãµµ¶ó",
			0, RGB(171, 154, 63));
	}
	
	//DrawRectMake(hdc, _box);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		DrawRectMake(hdc, _isidora);
		_stprintf_s(_loc, "x: %.2f y: %.2f", _pos.x, _pos.y);
		TextOut(hdc, _pos.x, _pos.y, _loc, strlen(_loc));
		
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}
}
