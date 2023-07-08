#include "Stdafx.h"
#include "MainMenu.h"

HRESULT MainMenu::init(void)
{
    IMAGEMANAGER->addFrameImage("���θ޴�_���", "Resources/Image/MainMenu/crisanta-bg.bmp",
        3200, 1080 , 5, 3, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("���θ޴�_ũ����Ÿ", "Resources/Image/MainMenu/crisanta-main-menu-anim.bmp",
        4480 , 720 , 7, 2, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("���θ޴�_����", "Resources/Image/MainMenu/crisanta-fg-petals.bmp",
        3200, 360, 5, 1, true, MAGENTA);
    IMAGEMANAGER->addFrameImage("���θ޴�_����2", "Resources/Image/MainMenu/crisanta-petals.bmp",
        7040 , 1440 , 11, 4, true, MAGENTA);

    IMAGEMANAGER->addFrameImage("����", "Resources/Image/Penitent/penitent_dodge_attack.bmp",
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

        IMAGEMANAGER->findImage("���θ޴�_���")->setFrameX(bg.x);
        IMAGEMANAGER->findImage("���θ޴�_���")->setFrameY(bg.y);

        IMAGEMANAGER->findImage("���θ޴�_ũ����Ÿ")->setFrameX(crisanta.x);
        IMAGEMANAGER->findImage("���θ޴�_ũ����Ÿ")->setFrameY(crisanta.y);

        IMAGEMANAGER->findImage("���θ޴�_����")->setFrameX(petal.x);
        IMAGEMANAGER->findImage("���θ޴�_����")->setFrameY(petal.y);

        IMAGEMANAGER->findImage("���θ޴�_����2")->setFrameX(petal_fg.x);
        IMAGEMANAGER->findImage("���θ޴�_����2")->setFrameY(petal_fg.y);
    }
}

void MainMenu::render(void)
{
    IMAGEMANAGER->frameRender("���θ޴�_���", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, bg.x, bg.y);
    IMAGEMANAGER->frameRender("���θ޴�_ũ����Ÿ", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, crisanta.x, crisanta.y);
    IMAGEMANAGER->frameRender("���θ޴�_����", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal.x, petal.y);
    IMAGEMANAGER->frameRender("���θ޴�_����2", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal_fg.x, petal_fg.y);
}
