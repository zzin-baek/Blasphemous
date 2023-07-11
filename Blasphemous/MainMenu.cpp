#include "Stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init(void)
{
    IMAGEMANAGER->addFrameImage("메인메뉴_배경", "Resources/Image/MainMenu/crisanta-bg.bmp",
        3200, 1080 , 5, 3, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("메인메뉴_크리산타", "Resources/Image/MainMenu/crisanta-main-menu-anim.bmp",
        4480 , 720 , 7, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("메인메뉴_꽃잎", "Resources/Image/MainMenu/crisanta-fg-petals.bmp",
        3200, 360, 5, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("메인메뉴_꽃잎2", "Resources/Image/MainMenu/crisanta-petals.bmp",
        7040 , 1440 , 11, 4, true, MAGENTA);

    IMAGEMANAGER->addFrameImage("애기천사", "Resources/Image/MainMenu/cherub.bmp",
        280 * 3 / 2, 210 * 3 / 2, 4, 3, true, MAGENTA);

    cnt = idx = 0;
    minus = 1;
    idx_bg = idx_crisanta = idx_petal = idx_petal_fg = 0;
    idx_angel = 0;
    bg = crisanta = petal = petal_fg = angel = { 0, 0 };

    return S_OK;
}

void MainMenu::release(void)
{
}

void MainMenu::update(void)
{
    cnt++;
    if (cnt % 22 == 0)
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
        else if (idx_crisanta == 0)
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

        IMAGEMANAGER->findImage("메인메뉴_배경")->setFrameX(bg.x);
        IMAGEMANAGER->findImage("메인메뉴_배경")->setFrameY(bg.y);

        IMAGEMANAGER->findImage("메인메뉴_크리산타")->setFrameX(crisanta.x);
        IMAGEMANAGER->findImage("메인메뉴_크리산타")->setFrameY(crisanta.y);

        IMAGEMANAGER->findImage("메인메뉴_꽃잎")->setFrameX(petal.x);
        IMAGEMANAGER->findImage("메인메뉴_꽃잎")->setFrameY(petal.y);

        IMAGEMANAGER->findImage("메인메뉴_꽃잎2")->setFrameX(petal_fg.x);
        IMAGEMANAGER->findImage("메인메뉴_꽃잎2")->setFrameY(petal_fg.y);
    }

    if (cnt % 5 == 0)
    {
        idx_angel++;
        if (idx_angel > 10)
        {
            idx_angel = 0;
        }

        angel.x = idx_angel % 4;
        angel.y = idx_angel / 4;

        IMAGEMANAGER->findImage("애기천사")->setFrameX(angel.x);
        IMAGEMANAGER->findImage("애기천사")->setFrameY(angel.y);
    }
}

void MainMenu::render(void)
{
    IMAGEMANAGER->frameRender("메인메뉴_배경", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, bg.x, bg.y);
    IMAGEMANAGER->frameRender("메인메뉴_크리산타", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, crisanta.x, crisanta.y);
    IMAGEMANAGER->frameRender("메인메뉴_꽃잎", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal.x, petal.y);
    IMAGEMANAGER->frameRender("메인메뉴_꽃잎2", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal_fg.x, petal_fg.y);

    // 테두리
    for (int i = 0; i < 3; i++)
    {
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 200, WINSIZE_Y - 250 + i, "Neo둥근모 Pro", 32, 2, "순례", strlen("순례"), RGB(0, 0, 0));
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 230, WINSIZE_Y - 210 + i, "Neo둥근모 Pro", 32, 2, "나가기", strlen("나가기"), RGB(0, 0, 0));
    }
    // 순례, 나가기
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 200, WINSIZE_Y - 250, "Neo둥근모 Pro", 32, 2, "순례", strlen("순례"), RGB(255, 255, 0));
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 230, WINSIZE_Y - 210, "Neo둥근모 Pro", 32, 2, "나가기", strlen("나가기"), RGB(255, 255, 255));
    IMAGEMANAGER->frameRender("애기천사", getMemDC(), WINSIZE_X - 120, WINSIZE_Y - 280, angel.x, angel.y);
}
