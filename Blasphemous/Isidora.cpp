#include "Stdafx.h"
#include "Isidora.h"

HRESULT Isidora::init(void)
{
	IMAGEMANAGER->addFrameImage("Isidora_Intro", "Resources/Image/Isidora/Isidora_introSequence.bmp",
		2560 * 2, 1290 * 2, 10, 5, true, MAGENTA);

	_pos = { WINSIZE_X / 2 + 210, WINSIZE_Y / 2 - 400 };
	_cnt = _idx = _idx_x = _idx_y = 0;

	return S_OK;
}

void Isidora::update(void)
{
	_cnt++;
	if (_cnt % 5 == 0)
	{
		if (_idx > 49)
		{
			_idx = 0;
		}

		_idx_x = _idx % 10;
		_idx_y = _idx / 10;

		IMAGEMANAGER->findImage("Isidora_Intro")->setFrameX(_idx_x);
		IMAGEMANAGER->findImage("Isidora_Intro")->setFrameY(_idx_y);

		_idx++;
	}

}

void Isidora::render(HDC hdc)
{
	IMAGEMANAGER->frameRender("Isidora_Intro", hdc, _pos.x, _pos.y, _idx_x, _idx_y);
}
