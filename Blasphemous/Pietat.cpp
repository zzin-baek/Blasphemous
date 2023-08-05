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
		250 * 3 / 2, 26 * 3 / 2, 10, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_destroy", "Resources/Image/Pietat/thorn_projectile_destroyed_anim.bmp",
		658 * 3 / 2, 48 * 3 / 2, 14, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_unravel", "Resources/Image/Pietat/thorn_projectile_unraveling_anim.bmp",
		1408 * 3 / 2, 45 * 3 / 2, 22, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("Thorn_unravel_destroy", "Resources/Image/Pietat/thorn_projectile_unraveled_destroyed_anim.bmp",
		2508 * 3 / 2, 120 * 3 / 2, 22, 1, true, MAGENTA);

	IMAGEMANAGER->addFrameImage("Thorn_tower", "Resources/Image/Pietat/thorns_tower_anim.bmp",
		640 * 3/2, 504 * 3/2, 10, 4, true, MAGENTA);

	SOUNDMANAGER->addWaveFileWithKey("wakeup", "Resources/Sound/pietat/WakeUp.wav");
	SOUNDMANAGER->addWaveFileWithKey("stomp", "Resources/Sound/pietat/PIETAT_STOMP.wav");

	_cnt = _patternNum = _introIndex = 0;
	_idx = _introIdx = { 0, 0 };
	_isLeft = _intro = _outro = _finIntro = _finOutro = false;
	_onceThorn = _isAttack = _hit = false;
	_doNothing = true;

	_intervalT = _phase = 1;
	_pos = { -542, 343 };
	_hp = 50;

	wsprintf(_strAction, "Pietat_appear");

	initSync();

	return S_OK;
}

void Pietat::initSync(void)
{
	_sync.insert({ "Pietat_appear", {5, {0, 0}, {0, 0}} });
	_sync.insert({ "Pietat_death", {7, {-100, 80}, {-70, 80}} });
	_sync.insert({ "Pietat_idle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_walk", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_walkToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_turnaround", {4, {-97, 32}, {-104, 32}} });

	_sync.insert({ "Pietat_stomp", {8, {-100, 30}, {-100, 30}} });

	_sync.insert({ "Pietat_smash", {4, {-90, 10}, {-140, 10}} });
	_sync.insert({ "Pietat_smashToIdle_reverse", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_smashToIdle", {5, {-100, 30}, {-100, 30}} });

	_sync.insert({ "Pietat_slash", {3, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spit_start", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spit", {5, {-80, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_spitToIdle", {5, {-100, 30}, {-100, 30}} });

	_sync.insert({ "Pietat_step1ToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_step2ToIdle", {5, {-100, 30}, {-100, 30}} });
	_sync.insert({ "Pietat_stomp", {5, {-100, 30}, {-100, 30}} });
}

void Pietat::update(void)
{
	// ������ ���� ����
	if (_hp <= 100 && _hp > 0)
		_phase = 2;
	else if (_hp <= 0)
	{
		_outro = true;
		SOUNDMANAGER->stopMp3WithKey("pietat");
	}

	_cnt++;
	if (_intro)
	{
		if (_doNothing)
		{
			SOUNDMANAGER->CheckAndReplayWithKey("wakeup");
			_doNothing = false;
		}
		showIntro();
	}
	else if (_outro && !_finOutro)
	{
		if (_doNothing)
		{
			if (!isEmpty())
				_pattern.clear();

			_pattern.push_back("Pietat_death");

			if (_isLeft)
				_idx.x = IMAGEMANAGER->findImage("Pietat_death")->getMaxFrameX();
			else
				_idx.x = 0;
			_doNothing = false;
		}

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

					if (_outro)
						cout << "death" << endl;

					_finOutro = true;
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

					if (_outro)
						cout << "death" << endl;		

					_finOutro = true;
				}
				if (!_pattern.empty())
					IMAGEMANAGER->findImage(_pattern.front())->setFrameX(_idx.x);
			}
		}
	}
	else if (!_intro && !_outro && _finIntro)
	{
		_center.x = (_hitBox.left + _hitBox.right) / 2;
		_center.y = (_hitBox.top + _hitBox.bottom) / 2;

		_dist = abs(_center.x - PLAYER->getCenterX());
		setAction("Pietat_idle");

		_isAttack = false;

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

		if (_ptState[HIT_PIETAT] && !_hit)
		{
			_hit = true;

			EFFECT->addEffect({ "blood2", 0, { (int)_center.x, (int)_center.y },
		  {0, 0} }, 2);
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

		spitState();
		spitMove();
		spitCycle();

		projectileCollision();

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
							if (_outro)
								cout << "death" << endl;
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
							if (_outro)
								cout << "death" << endl;
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

			SOUNDMANAGER->playEffectSoundWave("Resources/Sound/pietat/PIETAT_STOMP.wav");

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

			for (int i = 0; i < _phase; i++)
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
						_thorn[i]._center = { _temp - 140 * k, (float)_hitBox.bottom - 100 };
						_thorn[i]._idx = { 0, 0 };

						k++;
						if (k > 1)
							break;
					}
				}
				if (_idx.x <= IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 9)
				{
					_attack = RectMake(_hitBox.left - 150, _hitBox.bottom - 200, 150, 200);
					_isAttack = true;
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
						_thorn[i]._center = { _temp + 140 * k, (float)_hitBox.bottom - 100 };
						_thorn[i]._idx = { 0, 0 };

						k++;
						if (k > 1)
							break;
					}
				}
				if (_idx.x >= 9)
				{
					_attack = RectMake(_hitBox.right, _hitBox.bottom - 200, 150, 200);
					_isAttack = true;
				}
			}
		}
		if (!strcmp(_pattern.front(), "Pietat_smash"))
		{
			if (_isLeft)
			{
				if (_idx.x == IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 29 && !_onceThorn)
				{
					SOUNDMANAGER->playEffectSoundWave("Resources/Sound/pietat/PietatSmash.wav");
					_onceThorn = true;
					int k = 0;
					for (int i = 0; i < MAX_THORN; i++)
					{
						if (_thorn[i]._create) continue;

						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _center.x + 90 * (k + 1), (float)_hitBox.bottom - 90 };
						_thorn[i]._idx = { 0, 0 };

						_thorn[i + 1]._create = true;
						_thorn[i + 1]._cnt = 0;
						_thorn[i + 1]._center = { _center.x - 90 * (k + 1), (float)_hitBox.bottom - 90 };
						_thorn[i + 1]._idx = { 0, 0 };

						k++;
						if (k > 2 * _phase)
							break;
					}
				}
				if (_idx.x <= IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 29)
				{
					_attack = RectMakeCenter(_center.x, _hitBox.bottom - 150, 500, 150);
					_isAttack = true;
				}
			}
			else
			{
				if (_idx.x == 29 && !_onceThorn)
				{
					SOUNDMANAGER->playEffectSoundWave("Resources/Sound/pietat/PietatSmash.wav");
					_onceThorn = true;
					int k = 0;
					for (int i = 0; i < MAX_THORN; i += 2)
					{
						_thorn[i]._create = true;
						_thorn[i]._cnt = 0;
						_thorn[i]._center = { _center.x + 90 * (k + 1), (float)_hitBox.bottom - 90 };
						_thorn[i]._idx = { 0, 0 };

						_thorn[i + 1]._create = true;
						_thorn[i + 1]._cnt = 0;
						_thorn[i + 1]._center = { _center.x - 90 * (k + 1), (float)_hitBox.bottom - 90 };
						_thorn[i + 1]._idx = { 0, 0 };

						k++;
						if (k > 2 * _phase)
							break;
					}
				}
				if (_idx.x >= 29)
				{
					_attack = RectMakeCenter(_center.x, _hitBox.bottom - 150, 500, 150);
					_isAttack = true;
				}
			}
		}
		if (!strcmp(_pattern.front(), "Pietat_spit"))
		{
			if (_isLeft)
			{
				if (_idx.x == IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 1 && !_onceThorn)
				{
					_onceThorn = true;
					for (int i = 0; i < MAX_SPIT; i++)
					{
						if (_spit[i]._create) continue;

						_spit[i]._create = true;
						_spit[i]._center = { _center.x - 70, _center.y - 30 };
						_spit[i]._idx = { 0, 0 };
						_spit[i]._cnt = 0;
						_spit[i]._state = 1;
						_spit[i].angle = 150.0f;				

						break;
					}
				}
			}
			else
			{
				if (_idx.x == 1 && !_onceThorn)
				{
					_onceThorn = true;
					for (int i = 0; i < MAX_SPIT; i++)
					{
						if (_spit[i]._create) continue;

						_spit[i]._create = true;
						_spit[i]._center = { _center.x + 70, _center.y - 30 };
						_spit[i]._idx = { 0, 0 };
						_spit[i]._cnt = 0;
						_spit[i]._state = 1;
						_spit[i].angle = 30.0f;

						break;
					}
				}
			}
		}
		if (!strcmp(_pattern.front(), "Pietat_slash"))
		{
			if (_isLeft)
			{
				if (_idx.x <= IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 14
					&& _idx.x >= IMAGEMANAGER->findImage(_pattern.front())->getMaxFrameX() - 20)
				{
					_attack = RectMake(_hitBox.left - 200, _hitBox.bottom - 250, 200, 250);
					_isAttack = true;
				}
			}
			else
			{
				if (_idx.x >= 14 && _idx.x <= 20)
				{
					_attack = RectMake(_hitBox.right, _hitBox.bottom - 250, 200, 250);
					_isAttack = true;
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
				_thorn[i]._proj = RectMakeCenter(_thorn[i]._center.x, _thorn[i]._center.y,
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameWidth(),
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameHeight());
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
				_thorn[i]._proj = RectMakeCenter(_thorn[i]._center.x, _thorn[i]._center.y,
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameWidth(),
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameHeight());
			}

			if (_thorn[i + 1]._create && !_thorn[i + 1]._fire)
			{
				_thorn[i + 1]._fire = true;
				_thorn[i + 1]._proj = RectMakeCenter(_thorn[i + 1]._center.x, _thorn[i + 1]._center.y,
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameWidth(),
					IMAGEMANAGER->findImage("Thorn_tower")->getFrameHeight());
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

void Pietat::setProjectilePos(int x)
{
	for (int i = 0; i < MAX_THORN; i++)
	{
		if (!_thorn[i]._create) continue;

		_thorn[i]._center.x += x;
		_thorn[i]._proj.left += x;
		_thorn[i]._proj.right += x;
	}

	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (!_spit[i]._create) continue;

		_spit[i]._center.x += x;
		_spit[i]._proj.left += x;
		_spit[i]._proj.right += x;
	}
}

void Pietat::projectileCollision(void)
{
	RECT _rt;
	for (int i = 0; i < MAX_THORN; i++)
	{
		if (!_thorn[i]._create) continue;

		if (_thorn[i]._cnt > 23 && _thorn[i]._cnt < 31)
		{
			if (IntersectRect(&_rt, &_thorn[i]._proj, &PLAYER->getHitBox()) &&
				!PLAYER->getState()[DODGE] && !PLAYER->getState()[JUMP])
			{
				if (!PLAYER->getState()[HIT] && !PLAYER->getHit())
				{
					PLAYER->setHit(true);
					PLAYER->setHP(PLAYER->getHP() - 5);
				}
			}
		}
	}

	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (!_spit[i]._create) continue;
		if (_spit[i]._destroy) continue;

		if (IntersectRect(&_rt, &_spit[i]._proj, &PLAYER->getHitBox()))
		{
			if (!PLAYER->getState()[ATTACK] && !PLAYER->getAttack())
			{
				if (!PLAYER->getState()[HIT] && !PLAYER->getHit())
				{
					PLAYER->setHit(true);
					PLAYER->setHP(PLAYER->getHP() - 5);

					_spit[i]._destroy = true;
					if (!_spit[i]._cycle.empty())
						_spit[i]._cycle.clear();
					_spit[i]._cnt = 0;
				}
			}
		}
		if (IntersectRect(&_rt, &_spit[i]._proj, &PLAYER->getRect()))
		{
			if (PLAYER->getState()[ATTACK] || PLAYER->getAttack())
			{
				_spit[i]._destroy = true;
				if (!_spit[i]._cycle.empty())
					_spit[i]._cycle.clear();
				_spit[i]._cnt = 0;
			}
		}
	}
}

void Pietat::spitState(void)
{
	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (!_spit[i]._create) continue;

		if (_spit[i]._center.y >= _hitBox.bottom - 45)
			_spit[i]._state = 2;

		if (_spit[i]._cycle.empty())
		{
			if (_spit[i]._state == 1 && !_spit[i]._destroy)
				_spit[i]._cycle.push_back("Thorn");
			else if (_spit[i]._state == 1 && _spit[i]._destroy)
				_spit[i]._cycle.push_back("Thorn_destroy");
			else if (_spit[i]._state == 2 && !_spit[i]._destroy)
				_spit[i]._cycle.push_back("Thorn_unravel");
			else if (_spit[i]._state == 2 && _spit[i]._destroy)
				_spit[i]._cycle.push_back("Thorn_unravel_destroy");
		}
	}
}

void Pietat::spitCycle(void)
{
	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (_spit[i]._create && !_spit[i]._cycle.empty() && _cnt % 3 == 0)
		{
			_spit[i]._cnt++;

			_spit[i]._idx.x = _spit[i]._cnt % (IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameX() + 1);
			_spit[i]._idx.y = _spit[i]._cnt / (IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameX() + 1);
			
			if (_spit[i]._cnt > (IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameY() + 1) - 1)
			{
				if (!strcmp(_spit[i]._cycle.front(), "Thorn_unravel") && !_spit[i]._destroy)
				{
					_spit[i]._idx.x = IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameX();
					_spit[i]._idx.y = IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getMaxFrameX();
				}
				else if (_spit[i]._destroy)
				{
					_spit[i]._cnt = 0;
					_spit[i]._idx = { 0, 0 };
					_spit[i]._create = false;
					_spit[i]._destroy = false;

					_spit[i]._cycle.pop_front();
				}
				else
				{
					_spit[i]._cnt = 0;
					_spit[i]._idx = { 0, 0 };
					_spit[i]._cycle.pop_front();
				}
			}

			if (!_spit[i]._cycle.empty())
			{
				IMAGEMANAGER->findImage(_spit[i]._cycle.front())->setFrameX(_thorn[i]._idx.x);
				IMAGEMANAGER->findImage(_spit[i]._cycle.front())->setFrameY(_thorn[i]._idx.y);
			}

		}
	}
}

void Pietat::spitMove(void)
{
	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (!_spit[i]._create) continue;

		if (_spit[i]._state == 1)
		{
			if (_isLeft)
			{
				_spit[i]._center.x += 3.0f * cos(_spit[i].angle * PI / 180);
				_spit[i]._center.y += 4.0f * -sin(_spit[i].angle * PI / 180);

				if (!_spit[i]._cycle.empty())
				{
					_spit[i]._proj = RectMakeCenter(_spit[i]._center.x, _spit[i]._center.y,
						IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameWidth(),
						IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameHeight());
				}


				if (_spit[i].angle <= 245.0f)
					_spit[i].angle += 2.0f;
			}
			else
			{
				_spit[i]._center.x += 3.0f * cos(_spit[i].angle * PI / 180);
				_spit[i]._center.y += 4.0f * -sin(_spit[i].angle * PI / 180);

				if (!_spit[i]._cycle.empty())
				{
					_spit[i]._proj = RectMakeCenter(_spit[i]._center.x, _spit[i]._center.y,
						IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameWidth(),
						IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameHeight());
				}

				if (_spit[i].angle >= -55.0f)
					_spit[i].angle -= 2.0f;
			}
		}
		else
		{
			if (!_spit[i]._cycle.empty())
			{
				_spit[i]._proj = RectMakeCenter(_spit[i]._center.x, _spit[i]._center.y,
					IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameWidth(),
					IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameHeight());
			}
		}
	}
}

void Pietat::showIntro(void)
{
	if (_cnt % 8 == 0)
	{
		if (_introIndex > 85)
		{
			_intro = false;
			_finIntro = _doNothing = true;
			SOUNDMANAGER->CheckAndReplayWithKey("pietat");
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
			IMAGEMANAGER->frameRender("Thorn_tower", hdc,
				_thorn[i]._center.x - IMAGEMANAGER->findImage("Thorn_tower")->getFrameWidth() / 2,
				_thorn[i]._center.y - IMAGEMANAGER->findImage("Thorn_tower")->getFrameHeight() / 2,
				_thorn[i]._idx.x, _thorn[i]._idx.y);
		}
	}

	for (int i = 0; i < MAX_SPIT; i++)
	{
		if (_spit[i]._create && !_spit[i]._cycle.empty())
		{
			IMAGEMANAGER->frameRender(_spit[i]._cycle.front(), hdc,
				_spit[i]._center.x - IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameWidth() / 2, 
				_spit[i]._center.y - IMAGEMANAGER->findImage(_spit[i]._cycle.front())->getFrameHeight() / 2, 
				_spit[i]._idx.x, _spit[i]._idx.y);
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

		if (_isAttack)
			DrawRectMake(hdc, _attack);

		for (int i = 0; i < MAX_THORN; i++)
		{
			if (_thorn[i]._fire)
			{
				DrawRectMake(hdc, _thorn[i]._proj);
			}
		}

		for (int i = 0; i < MAX_SPIT; i++)
		{
			if (_spit[i]._create)
			{
				DrawRectMake(hdc, _spit[i]._proj);
			}
		}


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
			IMAGEMANAGER->findImage("Isidora_HP")->getWidth() * _hp / 200, IMAGEMANAGER->findImage("Isidora_HP")->getHeight());
		IMAGEMANAGER->render("Isidora_HP_Bar", hdc, 290, 634);
		FONTMANAGER->drawText(hdc, WINSIZE_X / 2 - 80, 612, "Neo�ձٸ� Pro", 30, 1, L"�� �ǿ��ٵ�",
			0, RGB(171, 154, 63));
	}
}