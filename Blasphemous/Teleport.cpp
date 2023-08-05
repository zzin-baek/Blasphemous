#include "Stdafx.h"
#include "Teleport.h"

HRESULT Teleport::init(void)
{
	IMAGEMANAGER->addImage("Room_teleport", "Resources/Image/BackGround/room.bmp", 1280, 720);
	IMAGEMANAGER->addImage("Room_teleport_collision", "Resources/Image/BackGround/room_collision.bmp",
		1280, 720, true, RGB(255, 255, 255));

	IMAGEMANAGER->addFrameImage("Portal", "Resources/Image/Sheet/bluePortal.bmp",
		456 * 2, 224 * 2, 6, 2, true, MAGENTA);

	_idx = { 0, 0 };
	_cnt = _ind = _nextStage = 0;
	_inPortal = false;
	_alpha = 0;

	return S_OK;
}

void Teleport::release(void)
{
}

void Teleport::update(void)
{
	PLAYER->playerAction();
	PLAYER->playerMove();

	if (!PLAYER->getFixed())
		PLAYER->setPosY(PLAYER->getPosY() + 5.0f);

	for (int i = PLAYER->getHitBox().left; i <= PLAYER->getHitBox().right; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("Room_teleport_collision")->getMemDC(),
			i, PLAYER->getRect().bottom);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			PLAYER->setGround(true);
			PLAYER->setPosY(PLAYER->getPosY() - 5.0f);
			break;
		}
		PLAYER->setGround(false);
	}

	_cnt++;
	if (_cnt % 10 == 0)
	{
		if (_ind > 12)
		{
			_ind = 0;
		}

		_idx.x = _ind % 6;
		_idx.y = _ind / 6;

		IMAGEMANAGER->findImage("Portal")->setFrameX(_idx.x);
		IMAGEMANAGER->findImage("Portal")->setFrameY(_idx.y);

		_ind++;
	}

	if (PLAYER->getPosX() + 70 >= WINSIZE_X - 180)
		_inPortal = true;

	if (_inPortal)
	{
		_alpha += 3;
		if (_alpha >= 255)
			_nextStage = 1;
	}
}

void Teleport::render(void)
{
	IMAGEMANAGER->render("Room_teleport", getMemDC(), 0, 0);
	IMAGEMANAGER->alphaFrameRender("Portal", getMemDC(), WINSIZE_X - 250, WINSIZE_Y / 2 + 60, 
		_idx.x, _idx.y, 56);

	PLAYER->renderPlayer(getMemDC());
	PLAYER->renderProfile(getMemDC());

	IMAGEMANAGER->alphaRender("Black_bg", getMemDC(), 0, 0, _alpha);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->render("Room_teleport_collision", getMemDC(), 0, 0);
	}
}
