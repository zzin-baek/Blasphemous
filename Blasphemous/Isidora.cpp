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
	IMAGEMANAGER->addFrameImage("Isidora_backToIdle", "Resources/Image/Isidora/Isidora_backToIdleFinal.bmp",
		798 * 2, 240 * 2, 6, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_outToCast", "Resources/Image/Isidora/Isidora_outToCastFinal.bmp",
		1463 * 2, 260 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToRising", "Resources/Image/Isidora/Isidora_outToRisingScytheFinal.bmp",
		1944 * 2, 294 * 2, 12, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_outToTwirl", "Resources/Image/Isidora/Isidora_outToTwirlFinal.bmp",
		1958 * 2, 262 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_risingAppear", "Resources/Image/Isidora/Isidora_risingScyAppear.bmp",
		528 * 2, 404 * 2, 3, 2, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Isidora_scy", "Resources/Image/Isidora/Isidora_risingScytheSequence.bmp",
		5516 * 2, 388 * 2, 28, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_scy2", "Resources/Image/Isidora/Isidora_risingScySequence2.bmp",
		6534 * 2, 432 * 2, 27, 2, true, MAGENTA);
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

	// 이펙트
	IMAGEMANAGER->addFrameImage("Isidora_screenslash_effect", "Resources/Image/Isidora/Isidora_screenslash_effect2.bmp",
		3647 * 2, 26 * 2, 7, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_sparkAppear", "Resources/Image/Isidora/IsidoraSparkAppear.bmp",
		864 * 2, 64 * 2, 9, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Isidora_sparkLoop", "Resources/Image/Isidora/IsidoraSparkLoop.bmp",
		576 * 2, 64 * 2, 6, 2, true, MAGENTA);

	// 불기둥
	IMAGEMANAGER->addFrameImage("Column_create", "Resources/Image/Isidora/FireColumnAnticipation.bmp",
		410 * 2, 1300 * 2, 5, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_create2", "Resources/Image/Isidora/FireColumnAnticipation2.bmp",
		1394 * 2, 325 * 2, 17, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_loop", "Resources/Image/Isidora/FireColumnLoop.bmp",
		328 * 2, 975 * 2, 4, 3, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Column_out", "Resources/Image/Isidora/FireColumnOut.bmp",
		328 * 2, 1300 * 2, 4, 4, true, MAGENTA);

	// 불똥
	IMAGEMANAGER->addFrameImage("FireBall_create", "Resources/Image/Isidora/IsidoraProjectileIn.bmp",
		507 * 2, 39 * 2, 13, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("FireBall_loop", "Resources/Image/Isidora/IsidoraProjectileLoop.bmp",
		507 * 2, 39 * 2, 12, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("FireBall_out", "Resources/Image/Isidora/IsidoraProjectileOut.bmp",
		507 * 2, 39 * 2, 13, 1, true, MAGENTA);

	IMAGEMANAGER->addImage("Circle_Mask", "Resources/Image/Sheet/Circle_Mask.bmp",
		130, 130, true, MAGENTA); //256  256
	IMAGEMANAGER->addImage("Column_Mask", "Resources/Image/Sheet/Column_Mask.bmp", 
		200, 680, true, MAGENTA); // 300, 1024

	// hp
	IMAGEMANAGER->addImage("Isidora_HP_Bar", "Resources/Image/Sheet/boss_healthBar.bmp",
		346 * 2, 30 * 2, true, MAGENTA);
	IMAGEMANAGER->addImage("Isidora_HP", "Resources/Image/Sheet/boss_healthBlood.bmp", 
		289 * 2, 8 * 2, true, MAGENTA);
	
	_pos = { WINSIZE_X / 2 + 380, WINSIZE_Y / 2 - 100};
	_idx = { 0, 0 };
	_cnt = _patternNum = 0;
	_interval = 10;

	_hp = 300;
	_phase = 1;

	_isLeft = _doNothing = true;
	_finIntro = _once = _once2 = false;

	// 5번 패턴 위치
	_risingSpot[0] = { 140, 500 };
	_risingSpot[1] = { 1130, 500 };
	_risingSpot[2] = { 600, 500 };
	
	tempX = 500.0f; 
	tempY = 500.0f;
	
	initSync();

	return S_OK;
}

void Isidora::initSync(void)
{
	_sync.insert({ "Isidora_Intro", { 6, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_Intro2", { 6, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_idle", { 5, {-12, 18}, {30, 18} } });
	_sync.insert({ "Isidora_backToIdle", {5, {10, 20}, {10, 20}} });
	_sync.insert({ "Isidora_vanish", { 4, {-10, 13}, {23, 13} } });
	_sync.insert({ "Isidora_outToCast", { 4, {-50, 15}, {65, 15} } });
	_sync.insert({ "Isidora_outToRising", { 3, {20, 30}, {0, 30} } });
	_sync.insert({ "Isidora_outToTwirl", { 4, {40, 10}, {-20, 10} } });
	_sync.insert({ "Isidora_risingAppear", { 5, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_scy", { 7, {20, 0}, {0, 0} } });
	_sync.insert({ "Isidora_scy2", { 7, {-10, -30}, {30, -30} } });
	_sync.insert({ "Isidora_slash", { 5, {0, -27}, {23, -27} } });
	_sync.insert({ "Isidora_screen_slash", { 6, {30, -10}, {0, -10} } });
	_sync.insert({ "Isidora_screenslash_effect", { 5, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_sparkAppear", {5, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_sparkLoop", {5, {0, 0}, {0, 0}} });
	_sync.insert({ "Isidora_twirl", { 4, {10, 8}, {10, 8} } });
	_sync.insert({ "Isidora_attackPattern", { 7, {10, -70}, {20, -80} } });
	_sync.insert({ "Isidora_twirlToVanish", { 4, {-10, 10}, {30, 10} } });
	_sync.insert({ "Isidora_slashToVanish", { 7, {0, 0}, {0, 0} } });
	_sync.insert({ "Isidora_cast", { 6, {-45, 20}, {45, 20} } });
}

void Isidora::update(void)
{
	_plPos = { PLAYER->getCenterX(), PLAYER->getCenterY() };
	_box = RectMakeCenter(_pos.x, _pos.y, 50, 50);

	if (_hp <= 200 && _hp > 100)
		_phase = 2;
	else if (_hp <= 100 && _hp > 0)
		_phase = 3;

	_cnt++;
	if (!_pattern.empty())
	{
		if (_seq.empty())
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
		else
		{
			if (_isLeft)
			{
				_idx.y = 1;
				IMAGEMANAGER->findImage(_pattern.front())->setFrameY(_idx.y);
				if (_cnt % _sync.find(_pattern.front())->second.timing == 0)
				{
					_idx.x--;
					if (_idx.x < IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - _seq.begin()->_current.y + 1)
					{
						if (_seq.begin()->_pass)
							_pattern.pop_front();
						
						_seq.erase(_seq.begin());
						
						if (!_pattern.empty())
						{
							cout << _pattern.front() << endl;
							_idx.x = IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX()
								- _seq.begin()->_current.x;
							_once2 = false;
							
						}
						else
						{
							if (!_finIntro) _finIntro = true;
							if (_patternNum != 3 && _patternNum != 5 && _patternNum != 4)
								_doNothing = true;
							if (!_seq.empty())
								_seq.clear();
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
					if (_idx.x > _seq.begin()->_current.y - 1)
					{
						if (_seq.begin()->_pass)
							_pattern.pop_front();

						_seq.erase(_seq.begin());
						if (!_pattern.empty())
						{
							//cout << _pattern.front() << endl;
							_idx.x = _seq.begin()->_current.x;
							_once2 = false;
						}
						else
						{
							if (!_finIntro) _finIntro = true;
							if (_patternNum != 3  && _patternNum != 5 && _patternNum != 4)
								_doNothing = true;
							if (!_seq.empty())
								_seq.clear();
						}
					}
					if (!_pattern.empty())
						IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx.x);
				}
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
		else
			_doNothing = false;

		if (!_pattern.empty())
		{
			if (!strcmp(_pattern.front(), "Isidora_cast") && _pos.y > 200)
				_pos.y -= 0.5f;
			if (!strcmp(_pattern.front(), "Isidora_vanish") && _pos.y < WINSIZE_Y / 2 + 100)
				_pos.y += 3.0f;
		}
		break;
	case 4:
		if (!_pattern.empty())
		{
			if (!strcmp(_pattern.front(), "Isidora_sparkLoop"))
			{
				if (_isLeft)
					_pos.x -= 10.0f;
				else
					_pos.x += 10.0f;

				tempX = _pos.x;
				//if (_pos.x > 500 )
				//{
				//	_seq.insert(_seq.begin() + 1, 1, { 0, {0, IMAGEMANAGER->findImage("Isidora_sparkLoop")->getMaxFrameX()} });
				//	//_seq.erase(_seq.begin());
				//}
				//else // 한 번만 되게
				//{
				//	if (!_once2)
				//	{
				//		_once2 = true;
				//		_seq.insert(_seq.begin() + 1, 1, { 1, {0, IMAGEMANAGER->findImage("Isidora_sparkLoop")->getMaxFrameX()} });
				//		//_seq.erase(_seq.begin() + 1);
				//		if (_isLeft)
				//			setIdxX(IMAGEMANAGER->findImage("Isidora_sparkLoop")->getMaxFrameX());
				//		else
				//			setIdxX(0);
				//	}
				//}
			}

			if (!strcmp(_pattern.front(), "Isidora_scy2"))
			{
				if (_isLeft)
				{
					_pos.x -= 4.0f;
					if (_pos.x <= tempX)
					{
						_pos.y = tempY - pow(3, (tempX - _pos.x) / 30);
					}

					if (!_once)
					{
						_interval = 20;
						for (int i = 0; i < 3; i++)
						{
							_cl[i]._clPos = { float(tempX - 280 - (80 * i)), 0 };
							_cl[i]._idx = { 0, 0 };
							_cl[i]._create = true;
						}
						_once = true;
					}
				}
				else
				{
					_pos.x += 4.0f;
					if (_pos.x >= tempX)
					{
						_pos.y = tempY - pow(3, (_pos.x - tempX) / 30);
					}

					if (!_once)
					{
						_interval = 20;
						for (int i = 0; i < 3; i++)
						{
							_cl[i]._clPos = { float(tempX + 280 + (80 * i)), 0 };
							_cl[i]._idx = { 0, 0 };
							_cl[i]._create = true;
						}
						_once = true;
					}
				}
			}

			if (!strcmp(_pattern.front(), "Isidora_outToRising"))
				_pos.y = 500;

			if (!strcmp(_pattern.front(), "Isidora_twirl"))
			{
				_pos.y += 3.0f;
			}
		}
		/*if (_cnt % 2 == 0)
		{
			_pos.x -= 6.0f;
			if (IntersectRect(&_rt, &PLAYER->getRect(), &_box) && !_fine)
			{
				tempX = PLAYER->getCenterX();
				_fine = true;
			}
			if (_pos.x <= tempX)
			{
				_pos.y = tempY - pow(3, (tempX - _pos.x) / 30);
				if (!_fine)
				{
					_fine = true;
					addPattern("Isidora_outToRising");
					addPattern("Isidora_scy2");
					addPattern("Isidora_twirl");
					addPattern("Isidora_backToIdle");
					addPattern("Isidora_vanish");

					addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToRising")->getMaxFrameX()} });
					addSeq({ 1, {20, IMAGEMANAGER->findImage("Isidora_scy2")->getMaxFrameX()} });
					addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
					addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
					addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
					addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
					addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX()} });
				}
			}

			if (_pos.y <= 100)
			{
				tempX = 500;
			}
		}*/
		break;
	case 5:
		if (_isLeft) _pos = _risingSpot[1];
		else _pos = _risingSpot[0];

		if (!_pattern.empty())
		{
			if (!strcmp(_pattern.front(), "Isidora_risingAppear") && !_once2)
			{
				_isLeft = !_isLeft; 
				_once2 = true;
			}
			if (!strcmp(_pattern.front(), "Isidora_screenslash_effect"))
			{
				_pos = _risingSpot[2];
			}
			if (!strcmp(_pattern.front(), "Isidora_slashToVanish"))
			{
				_pos = _risingSpot[!_isLeft];

				if (!_once2)
				{
					_interval = 1;
					for (int i = 0; i < 2; i++)
					{
						_cl[i]._clPos = { _risingSpot[!_isLeft].x - 60 + 50 * (i + 1), 0 };
						_cl[i]._idx = { 0, 0 };
						_cl[i]._create = true;
					}
					_once2 = true;
				}
			}
		}
		break;
	case 6:

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
				else if ((_patternNum == 4 && i == 2) || (_patternNum == 5 && i == 1) || (i == 6))
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
			if (_fb[i]._fire && _fb[i]._center.y <= 450)
			{
				cout << _fb[i]._center.y << endl;
				if (_fb[i]._trace)
				{
					ag = atan2((PLAYER->getCenterY() - _fb[i]._center.y),
						(_fb[i]._center.x - PLAYER->getCenterX()));

					cout << "ag" << ag * 180 / PI << endl;

					center.x = _fb[i]._center.x + 3 * cos((ag - (180 * PI / 180)));
					center.y = _fb[i]._center.y - 3 * sin((ag - (180 * PI / 180)));

					_fb[i]._center = { center.x, center.y };
					_fb[i]._angle = ag * 180 / PI - 180;

				}
				else
				{
					center.x = _fb[i]._center.x + 3 * cos((_fb[i]._angle + 2) * PI / 180);
					center.y = _fb[i]._center.y - 3 * sin((_fb[i]._angle + 2) * PI / 180);

					_fb[i]._center = { center.x, center.y };
					_fb[i]._angle += 2;

					if (_fb[i]._angle > 270)
					{
						_fb[i]._trace = true;
					}
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
					_fb[i]._fire = _fb[i]._create = _fb[i]._trace = false;
					_fb[i]._center = { WINSIZE_X / 2, WINSIZE_Y / 2 };
					_fb[i]._visible = true;

					if (i >= 3)
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
		//cout << _pattern.front()<< " idx "<<_idx.x << endl;
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
			_mask = RectMake(_fb[i]._center.x - 23, _fb[i]._center.y - 23, 130, 130);
			IMAGEMANAGER->alphaRender("Circle_Mask", hdc, _mask.left, _mask.top, 30);
			IMAGEMANAGER->frameRender(_fb[i]._cycle.front(), hdc,
				_fb[i]._center.x, _fb[i]._center.y, _fb[i]._idx.x, _fb[i]._idx.y);
		}
	}

	if (_hp > 0)
	{
		IMAGEMANAGER->render("Isidora_HP", hdc, 348, 680, 0, 0, 
			IMAGEMANAGER->findImage("Isidora_HP")->getWidth() * _hp / 300, IMAGEMANAGER->findImage("Isidora_HP")->getHeight());
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 654);
		FONTMANAGER->drawText(hdc, 360, 632, "Neo둥근모 Pro", 30, 1, L"죽은 자들을 위해 노래하는 성녀 이시도라",
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
