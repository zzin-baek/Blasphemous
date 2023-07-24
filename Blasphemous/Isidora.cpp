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

	IMAGEMANAGER->addImage("Circle_Mask", "Resources/Image/Sheet/Circle_Mask.bmp",
		256 * 2, 256 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Column_Mask", "Resources/Image/Sheet/Column_Mask.bmp", 
		300 * 2, 1024 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Isidora_HP_Bar", "Resources/Image/Sheet/boss_healthBar.bmp",
		346 * 2, 30 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Isidora_HP", "Resources/Image/Sheet/boss_healthBlood.bmp", 
		289 * 2, 8 * 2, true, MAGENTA);
	//_pos = { WINSIZE_X / 2 + 380, WINSIZE_Y / 2 - 400 };
	_pos = { WINSIZE_X / 2 + 380, WINSIZE_Y / 2 - 100};
	_cnt = _idx = _idx_x = _idx_y = _patternNum = 0;
	_test = { 1100.0f, 450.0f };

	_hp = 200;

	_isLeft = true;
	_finIntro = false;
	
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
	//cout << "size; "<<_pattern.size() << endl;
	_plPos = { PLAYER->getCenterX(), PLAYER->getCenterY() };
	_box = RectMakeCenter(_test.x, _test.y, 50, 50);

	//cout << _plPos.x << "   " << _plPos.y << endl;
	_cnt++;
	if (!_pattern.empty())
	{
		if (_isLeft)
		{
			_idx_y = 1;
			IMAGEMANAGER->findImage(_pattern.front())->setFrameY(_idx_y);
			if (_cnt % _sync.find(_pattern.front())->second.timing == 0)
			{
				_idx_x--;
				if (_idx_x < 1)
				{
					_pattern.pop_front();
					if (!_pattern.empty())
					{
						_idx_x = IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX();
					}
					else
					{
						if (!_finIntro) _finIntro = true;

						_doNothing = true;
					}
				}
				if (!_pattern.empty())
					IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx_x);
			}
		}
		else
		{
			_idx_y = 0;
			IMAGEMANAGER->findImage(_pattern.front())->setFrameY(_idx_y);
			if (_cnt % _sync.find(_pattern.front())->second.timing == 0)
			{
				_idx_x++;
				if (_idx_x > IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX())
				{
					_pattern.pop_front();
					if (!_pattern.empty())
					{
						_idx_x = 0;
					}
					else
					{
						if (!_finIntro) _finIntro = true;

						_doNothing = true;
					}
				}
				if (!_pattern.empty())
					IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx_x);
			}
		}
	}
	useSkill();
}

void Isidora::useSkill(void)
{
	RECT _rt;
	bool _fine = false;
	if (_finIntro)
	{
		if (_cnt % 2 == 0)
		{
			_test.x -= 4.0f;
			if (IntersectRect(&_rt, &PLAYER->getRect(), &_box) && !_fine)
			{
				tempX = PLAYER->getCenterX();
				_fine = true;
			}
			if (_test.x <= tempX)
			{
				_test.y = tempY - pow(M_E, (tempX - _test.x) / 20);
			}
			
			if (_test.y <= 100)
			{
				_test = { 1100, 450 };
				tempX = 500;
			}

			_pos = _test;
		}
	}
	switch (_patternNum)
	{
	case 1:
		break;
	case 2:
		if (!_pattern.empty())
		{

		}
		break;
	case 3:
		break;
	case 4:
		break;
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
				_isidora.top + _sync[_pattern.front()].left.y, _idx_x, _idx_y);
		}
		else
		{
			IMAGEMANAGER->frameRender(_pattern.front(), hdc,
				_isidora.left + _sync[_pattern.front()].right.x,
				_isidora.top + _sync[_pattern.front()].right.y, _idx_x, _idx_y);
		}
	}


	if (_hp > 0)
	{
		IMAGEMANAGER->render("Isidora_HP", hdc, 348, 680);
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 654);
		FONTMANAGER->drawText(hdc, 360, 632, "Neo둥근모 Pro", 30, 1, L"죽은 자들을 위해 노래하는 성녀 이시도라",
			0, RGB(171, 154, 63));
	}
	
	RectangleMake(hdc, _test.x, _test.y, 50, 50);

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
