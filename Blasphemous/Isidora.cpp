#include "Stdafx.h"
#include "Isidora.h"

HRESULT Isidora::init(void)
{
	IMAGEMANAGER->addFrameImage("Isidora_Intro", "Resources/Image/Isidora/Isidora_introSequence.bmp",
		2560 * 2, 1290 * 2, 10, 5, true, MAGENTA);

	_pos = { WINSIZE_X / 2 + 135, WINSIZE_Y / 2 - 400 };
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
