#include "Stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init(void)
{
    IMAGEMANAGER->addFrameImage("메인메뉴_배경", "Resources/Image/MainMenu/crisanta-bg.bmp",
        3200, 1080, 5, 3);
    IMAGEMANAGER->addFrameImage("메인메뉴_크리산타", "Resources/Image/MainMenu/crisanta-main-menu-anim.bmp",
        4480, 720, 7, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("메인메뉴_꽃잎", "Resources/Image/MainMenu/crisanta-fg-petals.bmp",
        3200, 360, 5, 1, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("메인메뉴_꽃잎2", "Resources/Image/MainMenu/crisanta-petals.bmp",
        7040, 1440, 11, 4, true, RGB(255, 0, 255));

    cnt = idx = 0;
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

    if (cnt % 15 == 0)
    {
        idx_bg++;
        idx_crisanta++;
        idx_petal++;
        idx_petal_fg++;
        if (idx_bg > 15)
        {
            idx_bg = 0;
        }
        if (idx_crisanta > 14)
        {
            idx_crisanta = 0;
        }
        if (idx_petal > 5)
        {
            idx_petal = 0;
        }
        if (idx_petal_fg > 44)
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

        IMAGEMANAGER->findImage("메인메뉴_배경")->setFrameX(bg.x);
        IMAGEMANAGER->findImage("메인메뉴_배경")->setFrameY(bg.y);

        IMAGEMANAGER->findImage("메인메뉴_크리산타")->setFrameX(crisanta.x);
        IMAGEMANAGER->findImage("메인메뉴_크리산타")->setFrameY(crisanta.y);

        IMAGEMANAGER->findImage("메인메뉴_꽃잎")->setFrameX(petal.x);
        IMAGEMANAGER->findImage("메인메뉴_꽃잎")->setFrameY(petal.y);

        IMAGEMANAGER->findImage("메인메뉴_꽃잎2")->setFrameX(petal_fg.x);
        IMAGEMANAGER->findImage("메인메뉴_꽃잎2")->setFrameY(petal_fg.y);
    }
}

void MainMenu::render(void)
{
    IMAGEMANAGER->frameRender("메인메뉴_배경", getMemDC(), 0, 0, bg.x, bg.y);
    IMAGEMANAGER->frameRender("메인메뉴_크리산타", getMemDC(), 0, 0, crisanta.x, crisanta.y);
    IMAGEMANAGER->frameRender("메인메뉴_꽃잎", getMemDC(), 0, 0, petal.x, petal.y);
    IMAGEMANAGER->frameRender("메인메뉴_꽃잎2", getMemDC(), 0, 0, petal_fg.x, petal_fg.y);
}
