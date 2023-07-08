#include "Stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init(void)
{
    IMAGEMANAGER->addFrameImage("¸ÞÀÎ¸Þ´º_¹è°æ", "Resources/Image/MainMenu/crisanta-bg.bmp",
        3200, 1080 , 5, 3, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("¸ÞÀÎ¸Þ´º_Å©¸®»êÅ¸", "Resources/Image/MainMenu/crisanta-main-menu-anim.bmp",
        4480 , 720 , 7, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ", "Resources/Image/MainMenu/crisanta-fg-petals.bmp",
        3200, 360, 5, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ2", "Resources/Image/MainMenu/crisanta-petals.bmp",
        7040 , 1440 , 11, 4, true, MAGENTA);

    IMAGEMANAGER->addFrameImage("´åÁö", "Resources/Image/Penitent/penitent_dodge_attack.bmp",
        2048, 512, 8, 4, true, MAGENTA);

    cnt = idx = 0;
    minus = 1;
    idx_bg = idx_crisanta = idx_petal = idx_petal_fg = 0;
    bg, crisanta, petal, petal_fg = { 0, 0 };

    return S_OK;
}

void MainMenu::release(void)
{
}

void MainMenu::update(void)
{
    cnt++;

    if (cnt % 20 == 0)
    {
        idx_bg++;
        idx_crisanta += 1 * minus;
        idx_petal++;
        idx_petal_fg++;

        if (idx_bg > 14)
        {
            idx_bg = 0;
        }
        if (idx_crisanta > 12)
        {
            minus = -1;
        }
        else if (idx_crisanta < 1)
        {
            minus = 1;
        }
        if (idx_petal > 4)
        {
            idx_petal = 0;
        }
        if (idx_petal_fg > 43)
        {
            idx_petal_fg = 0;
        }
        bg.x = idx_bg % 5;
        bg.y = idx_bg / 5;

        crisanta.x = idx_crisanta % 7;
        crisanta.y = idx_crisanta / 7;

        petal.x = idx_petal % 5;
        petal.y = idx_petal / 5;

        petal_fg.x = idx_petal_fg % 11;
        petal_fg.y = idx_petal_fg / 11;

        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_¹è°æ")->setFrameX(bg.x);
        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_¹è°æ")->setFrameY(bg.y);

        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_Å©¸®»êÅ¸")->setFrameX(crisanta.x);
        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_Å©¸®»êÅ¸")->setFrameY(crisanta.y);

        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ")->setFrameX(petal.x);
        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ")->setFrameY(petal.y);

        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ2")->setFrameX(petal_fg.x);
        IMAGEMANAGER->findImage("¸ÞÀÎ¸Þ´º_²ÉÀÙ2")->setFrameY(petal_fg.y);
    }
}

void MainMenu::render(void)
{
    IMAGEMANAGER->frameRender("¸ÞÀÎ¸Þ´º_¹è°æ", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, bg.x, bg.y);
    IMAGEMANAGER->frameRender("¸ÞÀÎ¸Þ´º_Å©¸®»êÅ¸", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, crisanta.x, crisanta.y);
    IMAGEMANAGER->frameRender("¸ÞÀÎ¸Þ´º_²ÉÀÙ", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal.x, petal.y);
    IMAGEMANAGER->frameRender("¸ÞÀÎ¸Þ´º_²ÉÀÙ2", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal_fg.x, petal_fg.y);
}
