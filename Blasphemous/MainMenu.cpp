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

    IMAGEMANAGER->addFrameImage("�ֱ�õ��", "Resources/Image/MainMenu/cherub.bmp",
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

        IMAGEMANAGER->findImage("���θ޴�_���")->setFrameX(bg.x);
        IMAGEMANAGER->findImage("���θ޴�_���")->setFrameY(bg.y);

        IMAGEMANAGER->findImage("���θ޴�_ũ����Ÿ")->setFrameX(crisanta.x);
        IMAGEMANAGER->findImage("���θ޴�_ũ����Ÿ")->setFrameY(crisanta.y);

        IMAGEMANAGER->findImage("���θ޴�_����")->setFrameX(petal.x);
        IMAGEMANAGER->findImage("���θ޴�_����")->setFrameY(petal.y);

        IMAGEMANAGER->findImage("���θ޴�_����2")->setFrameX(petal_fg.x);
        IMAGEMANAGER->findImage("���θ޴�_����2")->setFrameY(petal_fg.y);
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

        IMAGEMANAGER->findImage("�ֱ�õ��")->setFrameX(angel.x);
        IMAGEMANAGER->findImage("�ֱ�õ��")->setFrameY(angel.y);
    }
}

void MainMenu::render(void)
{
    IMAGEMANAGER->frameRender("���θ޴�_���", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, bg.x, bg.y);
    IMAGEMANAGER->frameRender("���θ޴�_ũ����Ÿ", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, crisanta.x, crisanta.y);
    IMAGEMANAGER->frameRender("���θ޴�_����", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal.x, petal.y);
    IMAGEMANAGER->frameRender("���θ޴�_����2", getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, petal_fg.x, petal_fg.y);

    // �׵θ�
    for (int i = 0; i < 3; i++)
    {
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 200, WINSIZE_Y - 250 + i, "Neo�ձٸ� Pro", 32, 2, "����", strlen("����"), RGB(0, 0, 0));
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 230, WINSIZE_Y - 210 + i, "Neo�ձٸ� Pro", 32, 2, "������", strlen("������"), RGB(0, 0, 0));
    }
    // ����, ������
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 200, WINSIZE_Y - 250, "Neo�ձٸ� Pro", 32, 2, "����", strlen("����"), RGB(255, 255, 0));
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X - 230, WINSIZE_Y - 210, "Neo�ձٸ� Pro", 32, 2, "������", strlen("������"), RGB(255, 255, 255));
    IMAGEMANAGER->frameRender("�ֱ�õ��", getMemDC(), WINSIZE_X - 120, WINSIZE_Y - 280, angel.x, angel.y);
}
