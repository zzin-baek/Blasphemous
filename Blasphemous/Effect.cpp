#include "Stdafx.h"
#include "Effect.h"

HRESULT Effect::init(void)
{
	// enemy blood
	IMAGEMANAGER->addFrameImage("blood", "Resources/Image/Effect/blood.bmp", 456 * 2, 34 * 2, 12, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("blood2", "Resources/Image/Effect/blood2.bmp", 880 * 2, 49 * 2, 11, 1, true, MAGENTA);


	// penitent effect
	IMAGEMANAGER->addFrameImage("running_dust", "Resources/Image/Effect/running_dust.bmp",
		45 * 2, 24 * 2, 3, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("jump_dust", "Resources/Image/Effect/jump_dust.bmp",
		60 * 2, 44 * 2, 4, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("dodge_effect", "Resources/Image/Effect/dodge_effect.bmp",
		946 * 2, 68 * 2, 11, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("parry_success_effect", "Resources/Image/Effect/parry_success_effect.bmp",
		940 * 2, 52 * 2, 10, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("pushback_effect", "Resources/Image/Effect/pushback_effect.bmp",
		450 * 2, 48 * 2, 10, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("throuwback_dust", "Resources/Image/Effect/throwback_dust.bmp",
		658 * 2, 54 * 2, 7, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("shielder_block", "Resources/Image/Effect/shield_blockEffect.bmp",
		768 * 2, 192 * 2, 8, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("attack_spark1", "Resources/Image/Effect/attack_spark1.bmp",
		798 * 2, 166 * 2, 6, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("attack_spark2", "Resources/Image/Effect/attack_spark2.bmp",
		930 * 2, 166 * 2, 6, 2, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("attack_spark3", "Resources/Image/Effect/attack_spark3.bmp",
		822 * 2, 204 * 2, 6, 2, true, MAGENTA);


	_cnt = 0;

	for (int i = 0; i < 5; i++)
		_idx[i] = { 0, 0 };
	
	return S_OK;
}

void Effect::addEffect(tagEffect effect, int vectorNum)
{
	switch (vectorNum)
	{
	case 1:
		if (!_plEffect.empty())
			_plEffect.clear();

		_plEffect.push_back(effect);
		plEffect = *_plEffect.begin();

		break;
	case 2:
		_bossEffect.push_back(effect);

		if(!_bossEffect.empty())
			bossEffect = *_bossEffect.begin();
		break;
	case 3:
		_acEffect.push_back(effect);

		if (!_acEffect.empty())
			acEffect = *_acEffect.begin();
		break;
	case 4:
		_shEffect.push_back(effect);

		if (!_shEffect.empty())
			shEffect = *_shEffect.begin();
		break;
	case 5:
		_stEffect.push_back(effect);

		if (!_stEffect.empty())
			stEffect = *_stEffect.begin();
		break;
	}
}

void Effect::updateEffect(void)
{
	_cnt++;
	if (!_plEffect.empty())
	{
		if (PLAYER->getLeft())
		{
			plEffect._idx.y = 1;
			IMAGEMANAGER->findImage(plEffect._effect)->setFrameY(plEffect._idx.y);
			if (_cnt % 3 == 0)
			{
				plEffect._idx.x--;

				if (plEffect._idx.x < 1)
				{
					_plEffect.erase(_plEffect.begin());
				}
				if (!_plEffect.empty())
					IMAGEMANAGER->findImage(plEffect._effect)->setFrameX(plEffect._idx.x);
			}
		}
		else
		{
			plEffect._idx.y = 0;
			IMAGEMANAGER->findImage(plEffect._effect)->setFrameY(plEffect._idx.y);
			if (_cnt % 3 == 0)
			{
				plEffect._idx.x++;

				if (plEffect._idx.x > IMAGEMANAGER->findImage(plEffect._effect)->getMaxFrameX())
				{
					_plEffect.erase(_plEffect.begin());
				}
				if (!_plEffect.empty())
					IMAGEMANAGER->findImage(plEffect._effect)->setFrameX(plEffect._idx.x);
			}
		}
	}

	if (!_bossEffect.empty())
	{
		if (_cnt % 2 == 0)
		{
			if (bossEffect._cnt > (IMAGEMANAGER->findImage(bossEffect._effect)->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(bossEffect._effect)->getMaxFrameY() + 1) - 1)
			{
				_bossEffect.erase(_bossEffect.begin());
			}

			bossEffect._idx.x = bossEffect._cnt % 
				IMAGEMANAGER->findImage(bossEffect._effect)->getMaxFrameX() + 1;
			bossEffect._idx.y = bossEffect._cnt / 
				IMAGEMANAGER->findImage(bossEffect._effect)->getMaxFrameX() + 1;

			IMAGEMANAGER->findImage(bossEffect._effect)->setFrameX(bossEffect._idx.x);
			IMAGEMANAGER->findImage(bossEffect._effect)->setFrameY(bossEffect._idx.y);

			bossEffect._cnt++;
		}
	}

	if (!_acEffect.empty())
	{
		if (_cnt % 2 == 0)
		{
			if (acEffect._cnt > (IMAGEMANAGER->findImage(acEffect._effect)->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(acEffect._effect)->getMaxFrameY() + 1) - 1)
			{
				_acEffect.erase(_acEffect.begin());
			}

			acEffect._idx.x = acEffect._cnt %
				IMAGEMANAGER->findImage(acEffect._effect)->getMaxFrameX() + 1;
			acEffect._idx.y = acEffect._cnt /
				IMAGEMANAGER->findImage(acEffect._effect)->getMaxFrameX() + 1;

			IMAGEMANAGER->findImage(acEffect._effect)->setFrameX(acEffect._idx.x);
			IMAGEMANAGER->findImage(acEffect._effect)->setFrameY(acEffect._idx.y);

			acEffect._cnt++;
		}
	}

	if (!_shEffect.empty())
	{
		if (_cnt % 2 == 0)
		{
			if (shEffect._cnt > (IMAGEMANAGER->findImage(shEffect._effect)->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(shEffect._effect)->getMaxFrameY() + 1) - 1)
			{
				_shEffect.erase(_shEffect.begin());
			}

			shEffect._idx.x = shEffect._cnt %
				IMAGEMANAGER->findImage(shEffect._effect)->getMaxFrameX() + 1;
			shEffect._idx.y = shEffect._cnt /
				IMAGEMANAGER->findImage(shEffect._effect)->getMaxFrameX() + 1;

			IMAGEMANAGER->findImage(shEffect._effect)->setFrameX(shEffect._idx.x);
			IMAGEMANAGER->findImage(shEffect._effect)->setFrameY(shEffect._idx.y);

			shEffect._cnt++;
		}
	}

	if (!_stEffect.empty())
	{
		if (_cnt % 2 == 0)
		{
			if (stEffect._cnt > (IMAGEMANAGER->findImage(stEffect._effect)->getMaxFrameX() + 1) *
				(IMAGEMANAGER->findImage(stEffect._effect)->getMaxFrameY() + 1) - 1)
			{
				_stEffect.erase(_stEffect.begin());
			}

			stEffect._idx.x = stEffect._cnt %
				IMAGEMANAGER->findImage(stEffect._effect)->getMaxFrameX() + 1;
			stEffect._idx.y = stEffect._cnt /
				IMAGEMANAGER->findImage(stEffect._effect)->getMaxFrameX() + 1;

			IMAGEMANAGER->findImage(stEffect._effect)->setFrameX(stEffect._idx.x);
			IMAGEMANAGER->findImage(stEffect._effect)->setFrameY(stEffect._idx.y);

			stEffect._cnt++;
		}
	}
}

void Effect::renderEffect(HDC hdc)
{
	if (!_plEffect.empty())
	{
		IMAGEMANAGER->frameRender(plEffect._effect, hdc,
			plEffect._pos.x - IMAGEMANAGER->findImage(plEffect._effect)->getFrameWidth() / 2,
			plEffect._pos.y - IMAGEMANAGER->findImage(plEffect._effect)->getFrameHeight() / 2,
			plEffect._idx.x, plEffect._idx.y);
	}

	if (!_bossEffect.empty())
	{
		IMAGEMANAGER->frameRender(bossEffect._effect, hdc,
			bossEffect._pos.x - IMAGEMANAGER->findImage(bossEffect._effect)->getFrameWidth() / 2,
			bossEffect._pos.y - IMAGEMANAGER->findImage(bossEffect._effect)->getFrameHeight() / 2,
			bossEffect._idx.x, bossEffect._idx.y);
	}

	if (!_acEffect.empty())
	{
		IMAGEMANAGER->frameRender(acEffect._effect, hdc,
			acEffect._pos.x - IMAGEMANAGER->findImage(acEffect._effect)->getFrameWidth() / 2,
			acEffect._pos.y - IMAGEMANAGER->findImage(acEffect._effect)->getFrameHeight() / 2,
			acEffect._idx.x, acEffect._idx.y);
	}

	if (!_shEffect.empty())
	{
		IMAGEMANAGER->frameRender(shEffect._effect, hdc,
			shEffect._pos.x - IMAGEMANAGER->findImage(shEffect._effect)->getFrameWidth() / 2,
			shEffect._pos.y - IMAGEMANAGER->findImage(shEffect._effect)->getFrameHeight() / 2,
			shEffect._idx.x, shEffect._idx.y);
	}

	if (!_stEffect.empty())
	{
		IMAGEMANAGER->frameRender(stEffect._effect, hdc,
			stEffect._pos.x - IMAGEMANAGER->findImage(stEffect._effect)->getFrameWidth() / 2,
			stEffect._pos.y - IMAGEMANAGER->findImage(stEffect._effect)->getFrameHeight() / 2,
			stEffect._idx.x, stEffect._idx.y);
	}
}