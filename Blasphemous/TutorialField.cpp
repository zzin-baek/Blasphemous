#include "Stdafx.h"
#include "TutorialField.h"

HRESULT TutorialField::init(void)
{
    IMAGEMANAGER->addImage("tutorial_bg", "Resources/Image/BackGround/tutorial_bg.bmp",
        WINSIZE_X, WINSIZE_Y, true);
    IMAGEMANAGER->addImage("tutorial_bg2", "Resources/Image/BackGround/tutorial_bg2.bmp",
        WINSIZE_X, WINSIZE_Y, true, MAGENTA);
    IMAGEMANAGER->addImage("tutorial_map", "Resources/Image/BackGround/tutorial_map.bmp",
        1280, 720, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("priedieu", "Resources/Image/BackGround/priedieu_stand_anim.bmp",
        396 * 2, 146 * 2, 6, 1, true, MAGENTA);

    IMAGEMANAGER->addImage("tutorial_map_collision", "Resources/Image/BackGround/tutorial_map_collision.bmp",
        1280, 720, true, RGB(255, 255, 255));

    _cnt = _num = 0;
    _idx = { 0, 0 };

    return S_OK;
}

void TutorialField::update(void)
{
    _cnt++;
    if (_cnt % 10 == 0)
    {
        _num++;
        if (_num > 5)
            _num = 0;

        _idx.x = _num;
        _idx.y = 0;
    }
}


void TutorialField::render(HDC hdc)
{
    IMAGEMANAGER->render("tutorial_bg", hdc, 0, -200);
    //IMAGEMANAGER->render("tutorial_bg2", hdc, 0, 0);

    IMAGEMANAGER->render("tutorial_map", hdc, 0, 0);
    IMAGEMANAGER->frameRender("priedieu", hdc,
        WINSIZE_X / 2 - 50, WINSIZE_Y - 380, _idx.x, _idx.y);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        IMAGEMANAGER->render("tutorial_map_collision", hdc, 0, 0);
    }

}
