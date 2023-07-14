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

    IMAGEMANAGER->addImage("tutorial_map_collision", "Resources/Image/BackGround/tutorial_map_collision.bmp",
        1280, 720, true, RGB(255, 255, 255));

    return S_OK;
}


void TutorialField::render(HDC hdc)
{
    IMAGEMANAGER->render("tutorial_bg", hdc, 0, -200);
    //IMAGEMANAGER->render("tutorial_bg2", hdc, 0, 0);

    IMAGEMANAGER->render("tutorial_map", hdc, 0, 0);

    if (KEYMANAGER->isToggleKey(VK_TAB))
    {
        IMAGEMANAGER->render("tutorial_map_collision", hdc, 0, 0);
    }

}
