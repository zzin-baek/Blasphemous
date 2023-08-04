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
	IMAGEMANAGER->addFrameImage("Pietat_turnaround", "Resources/Image/Pietat/pietat_turnaround2.bmp",
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

	_cnt = _patternNum = _introIndex = 0;
	_idx = _introIdx = { 0, 0 };
	_isLeft = _intro = _outro = _finIntro = false;
	_onceThorn = false;
	_doNothing = true;

	_intervalT = 1;
	_pos = { -542, 343 };
	_hp = 100;

	wsprintf(_strAction, "Pietat_appear");

	initSync();

	return S_OK;
}

void Pietat::initSync(void)
{
	_sync.insert({ "Pietat_appear", {5, {0, 0}, {0, 0}} });
	_sync.insert({ "Pietat_death", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_idle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_walk", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_walkToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_turnaround", {4, {-97, 32}, {-104, 32}} });

	_sync.insert({ "Pietat_smash", {5, {-100, 10}, {-140, 10}} });
	_sync.insert({ "Pietat_smashToIdle_reverse", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_smashToIdle", {5, {-100, 30}, {-100, 30}} });

	_sync.insert({ "Pietat_slash", {3, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spit_start", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spit", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spitToIdle", {5, {-100, 30}, {-100, 30}} });

	_sync.insert({ "Pietat_stomp", {8, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_step1ToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_step2ToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_stomp", {5, {-100, 30}, {-100, 30}} });
}

void Pietat::update(void)
{
	_cnt++;
	if (_intro)
	{
		showIntro();
	}
	else if (!_intro && !_outro && _finIntro)
	{
		_center.x = (_hitBox.left + _hitBox.right) / 2;
		_center.y = (_hitBox.top + _hitBox.bottom) / 2;

		_dist = abs(_center.x - PLAYER->getCenterX());
		setAction("Pietat_idle");

		if (_center.x <= PLAYER->getCenterX())
		{
			if (_isLeft && isEmpty())
			{
				_pattern.push_back("Pietat_turnaround");
				_isLeft = false;

				_idx.x = 0;
			}
			else if (_dist > 200 && isEmpty())
			{
				setAction("Pietat_walk");
				_pos.x += 3.0f;
			}
		}
		else
		{
			if (!_isLeft && isEmpty())
			{
				_pattern.push_back("Pietat_turnaround");
				_isLeft = true;

				_idx.x = IMAGEMANAGER->findImage("Pietat_turnaround")->getMaxFrameX();
			}
			else if (_dist > 200 && isEmpty())
			{
				setAction("Pietat_walk");
				_pos.x -= 3.0f;
			}
		}

		if (_dist <= 200 && isEmpty())
		{
			if (_doNothing)
			{
				_patternNum = RND->getFromIntTo(1, 4); 
				useSkill();
			}
		}

		attack();
		if (_cnt % _intervalT == 0)
			thornCreate();

		thornCycle();

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
						_onceThorn = false;
						if (!_pattern.empty())
						{
							_idx.x = IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX();
						}
						else
						{
							_ptState.reset();
							_doNothing = true;
							_patternNum = 0;
							setAction("Pietat_idle");
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
					if (_idx.x > IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() + 1)
					{
						_pattern.pop_front();
						_onceThorn = false;
						if (!_pattern.empty())
						{
							_idx.x = 0;
						}
						else
						{
							_ptState.reset();
							_doNothing = true;
							_patternNum = 0;
							setAction("Pietat_idle");
						}
					}
					if (!_pattern.empty())
						IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx.x);
				}
			}
		}
		else
		{
			if (_isLeft)
			{
				_idx.y = 1;
				IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx.y);
				if (_cnt % _sync.find(_strAction)->second.timing == 0)
				{
					_idx.x--;
					if (_idx.x < 1)
					{

						_idx.x = IMAGEMANAGER->findImage(_strAction)->getMaxFrameX();
					}
					IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx.x);
				}
			}
			else
			{
				_idx.y = 0;
				IMAGEMANAGER->findImage(_strAction)->setFrameY(_idx.y);
				if (_cnt % _sync.find(_strAction)->second.timing == 0)
				{
					_idx.x++;
					if (_idx.x > IMAGEMANAGER->findImage(_strAction)->getMaxFrameX())
					{

						_idx.x = 0;

					}
					IMAGEMANAGER->findImage(_strAction)->setFrameX(_idx.x);
				}
			}
		}
	}
}

void Pietat::useSkill(void)
{
	switch (_patternNum)
	{
	case 1:
		_intervalT = 35;

		if (_doNothing)
		{
			_pattern.push_back("Pietat_stomp");
			_pattern.push_back("Pietat_step1ToIdle");

			if (_isLeft)
				_idx.x = IMAGEMANAGER->findImage("Pietat_stomp")->getMaxFrameX();
			else
				_idx.x = 0;

			_doNothing = false;
		}
		break;
	case 2:
		_intervalT = 15;

		if (_doNothing)
		{
			_pattern.push_back("Pietat_smash");
			_pattern.push_back("Pietat_smashToIdle");

			if (_isLeft)
				_idx.x = IMAGEMANAGER->findImage("Pietat_smash")->getMaxFrameX() + 1;
			else
				_idx.x = 0;

			_doNothing = false;
		}
		break;
	case 3: //spit
		if (_doNothing)
		{
			_pattern.push_back("Pietat_spit_start");
			_pattern.push_back("Pietat_spit");
			_pattern.push_back("Pietat_spitToIdle");

			if (_isLeft)
				_idx.x = IMAGEMANAGER->findImage("Pietat_spit_start")->getMaxFrameX() + 1;
			else
				_idx.x = 0;

			_doNothing = false;
		}
		break;
	case 4:
		if (_doNothing)
		{
			_pattern.push_back("Pietat_slash");

			if (_isLeft)
				_idx.x = IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX();
			else
				_idx.x = 0;

			_doNothing = false;
		}
		break;
	}
}

void Pietat::attack(void)
{
	if (!_pattern.empty())
	{
		if (!strcmp(_pattern.front(), "Pietat_stomp"))
		{
			if (_isLeft)
			{
				if (_idx.x == IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 9 && !_onceThorn)
				{
					_onceThorn = true;
					int k = 0;
					_temp = PLAYER->getCenterX();
					for (int i = 0; i < MAX_THORN; i++)
					{
						if (_thorn[i]._create) continue;

						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _temp - 140 * k, (float)_hitBox.bottom };
						_thorn[i]._idx = { 0, 0 };

						k++;
						if (k > 1)
							break;
					}
				}
			}
			else
			{
				if (_idx.x == 9 && !_onceThorn)
				{
					_onceThorn = true;
					int k = 0;
					_temp = PLAYER->getCenterX();
					for (int i = 0; i < MAX_THORN; i++)
					{
						if (_thorn[i]._create) continue;

						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _temp + 140 * k, (float)_hitBox.bottom };
						_thorn[i]._idx = { 0, 0 };

						k++;
						if (k > 1)
							break;
					}
				}
			}
		}
		if (!strcmp(_pattern.front(), "Pietat_smash"))
		{
			if (_isLeft)
			{
				if (_idx.x == IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 29 && !_onceThorn)
				{
					_onceThorn = true;
					int k = 0;
					for (int i = 0; i < MAX_THORN; i++)
					{
						if (_thorn[i]._create) continue;

						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _center.x + 30 + 100 * (k + 1), (float)_hitBox.bottom + 15 };
						_thorn[i]._idx = { 0, 0 };

						_thorn[i + 1]._create = true;
						_thorn[i + 1]._cnt = 0;
						_thorn[i + 1]._center = { _center.x - 30 - 100 * (k + 1), (float)_hitBox.bottom + 15 };
						_thorn[i + 1]._idx = { 0, 0 };

						k++;
						if (k > 2)
							break;
					}
				}
			}
			else
			{
				if (_idx.x == 29 && !_onceThorn)
				{
					_onceThorn = true;
					int k = 0;
					for (int i = 0; i < MAX_THORN; i += 2)
					{
						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _center.x + 30 + 100 * (k + 1), (float)_hitBox.bottom + 15 };
						_thorn[i]._idx = { 0, 0 };

						_thorn[i + 1]._create = true;
						_thorn[i + 1]._cnt = 0;
						_thorn[i + 1]._center = { _center.x - 30 - 100 * (k + 1), (float)_hitBox.bottom + 15 };
						_thorn[i + 1]._idx = { 0, 0 };

						k++;
						if (k > 2)
							break;
					}
				}
			}
		}
	}
}

void Pietat::thornCreate(void)
{
	if (_patternNum == 1)
	{
		for (int i = 0; i < MAX_THORN; i++)
		{
			if (_thorn[i]._create && !_thorn[i]._fire)
			{
				_thorn[i]._fire = true;
				break;
			}
		}
	}

	else if (_patternNum == 2)
	{
		for (int i = 0; i < MAX_THORN; i += 2)
		{
			if (_thorn[i]._create && !_thorn[i]._fire)
			{
				_thorn[i]._fire = true;
			}

			if (_thorn[i + 1]._create && !_thorn[i + 1]._fire)
			{
				_thorn[i + 1]._fire = true;
				break;
			}
		}
	}
}

void Pietat::thornCycle(void)
{
	for (int i = 0; i < MAX_THORN; i++)
	{
		if (_thorn[i]._fire && _cnt % 2 == 0)
		{
			_thorn[i]._cnt++;

			_thorn[i]._idx.x = _thorn[i]._cnt % (IMAGEMANAGER->findImage("Thorn_tower")->getMaxFrameX() + 1);
			_thorn[i]._idx.y = _thorn[i]._cnt / (IMAGEMANAGER->findImage("Thorn_tower")->getMaxFrameX() + 1);

			IMAGEMANAGER->findImage("Thorn_tower")->setFrameX(_thorn[i]._idx.x);
			IMAGEMANAGER->findImage("Thorn_tower")->setFrameY(_thorn[i]._idx.y);

			if (_thorn[i]._cnt > (IMAGEMANAGER->findImage("Thorn_tower")->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage("Thorn_tower")->getMaxFrameY() + 1) - 1)
			{
				_thorn[i]._create = false;
				_thorn[i]._fire = false;
				_thorn[i]._cnt = 0;
				_thorn[i]._center = { 0, 0 };
				_thorn[i]._idx = { 0, 0 };
			}
		}
	}
}

void Pietat::setThornPos(int x)
{
	for (int i = 0; i < MAX_THORN; i++)
	{
		if (!_thorn[i]._create) continue;

		_thorn[i]._center.x += x;
	}
}

void Pietat::showIntro(void)
{
	if (_cnt % 8 == 0)
	{
		if (_introIndex > 85)
		{
			_intro = false;
			_finIntro = true;
			wsprintf(_strAction, "Pietat_idle");
		}

		_introIdx.x = _introIndex % 11;
		_introIdx.y = _introIndex / 11;

		IMAGEMANAGER->findImage(_strAction)->setFrameX(_introIdx.x);
		IMAGEMANAGER->findImage(_strAction)->setFrameY(_introIdx.y);
		
		_introIndex++;
	}
}

void Pietat::render(HDC hdc)
{
	if (!_pattern.empty())
	{
		_pietat = RectMakeCenter(_pos.x, _pos.y,
			IMAGEMANAGER->findImage(_pattern.front())->getFrameWidth(),
			IMAGEMANAGER->findImage(_pattern.front())->getFrameHeight());

		if (_isLeft)
		{
			IMAGEMANAGER->frameRender(_pattern.front(), hdc,
				_pietat.left + _sync[_pattern.front()].left.x,
				_pietat.top + _sync[_pattern.front()].left.y, _idx.x, _idx.y);

			_hitBox = RectMakeCenter(_pos.x + _sync.find(_pattern.front())->second.left.x,
				_pos.y + _sync.find(_pattern.front())->second.left.y, 200, 450);
		}
		else
		{
			IMAGEMANAGER->frameRender(_pattern.front(), hdc,
				_pietat.left + _sync[_pattern.front()].right.x,
				_pietat.top + _sync[_pattern.front()].right.y, _idx.x, _idx.y);

			_hitBox = RectMakeCenter(_pos.x + _sync.find(_pattern.front())->second.right.x,
				_pos.y + _sync.find(_pattern.front())->second.right.y, 200, 450);
		}
	}
	else
	{
		_pietat = RectMakeCenter(_pos.x, _pos.y,
			IMAGEMANAGER->findImage(_strAction)->getFrameWidth(),
			IMAGEMANAGER->findImage(_strAction)->getFrameHeight());

		if (!strcmp(_strAction, "Pietat_appear"))
			IMAGEMANAGER->frameRender(_strAction, hdc, _pos.x - IMAGEMANAGER->findImage(_strAction)->getFrameWidth() / 2,
				_pos.y - IMAGEMANAGER->findImage(_strAction)->getFrameHeight() / 2, _introIdx.x, _introIdx.y);
		else
		{
			if (_isLeft)
			{
				IMAGEMANAGER->frameRender(_strAction, hdc,
					_pietat.left + _sync.find(_strAction)->second.left.x,
					_pietat.top + _sync.find(_strAction)->second.left.y,
					_idx.x, _idx.y);

				_hitBox = RectMakeCenter(_pos.x + _sync.find(_strAction)->second.left.x,
					_pos.y + _sync.find(_strAction)->second.left.y, 200, 450);
			}
			else
			{
				IMAGEMANAGER->frameRender(_strAction, hdc,
					_pietat.left + _sync.find(_strAction)->second.right.x,
					_pietat.top + _sync.find(_strAction)->second.right.y,
					_idx.x, _idx.y);

				_hitBox = RectMakeCenter(_pos.x + _sync.find(_strAction)->second.right.x,
					_pos.y + _sync.find(_strAction)->second.right.y, 200, 450);
			}
		}
	}

	for (int i = 0; i < MAX_THORN; i++)
	{
		if (_thorn[i]._fire)
		{
			//_mask = RectMake(_thorn[i]._clPos.x - 100, _cl[i]._clPos.y, 164, 650);

			IMAGEMANAGER->frameRender("Thorn_tower", hdc,
				_thorn[i]._center.x - 80, _thorn[i]._center.y - 250, _thorn[i]._idx.x, _thorn[i]._idx.y);
		}
	}

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

void Pietat::renderHP(HDC hdc)
{
	if (_hp > 0)
	{
		IMAGEMANAGER->render("Isidora_HP", hdc, 348, 660, 0, 0,
			IMAGEMANAGER->findImage("Isidora_HP")->getWidth() * _hp / 100, IMAGEMANAGER->findImage("Isidora_HP")->getHeight());
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 634);
		FONTMANAGER->drawText(hdc, WINSIZE_X / 2 - 80, 612, "NeoµÕ±Ù¸ð Pro", 30, 1, L"ÅÙ ÇÇ¿¡´Ùµå",
			0, RGB(171, 154, 63));
	}
}
