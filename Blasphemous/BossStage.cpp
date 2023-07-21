#include "Stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init(void)
{
    _bm = new BossMap;
    _bm->init();

    //PLAYER = new Player;

    _boss = new Isidora;
    _boss->init();

    _startPos = RectMakeCenter(490, 490, 50, 60);
    _intro = false;
    _cnt = 0;

    return S_OK;
}

void BossStage::release(void)
{
    SAFE_DELETE(_bm);
}

void BossStage::update(void)
{
    if (!_intro)
    {
        PLAYER->playerAction();
        PLAYER->playerMove();


        if (!PLAYER->getFixed())
            PLAYER->setPosY(PLAYER->getPosY() + 5.0f);

        if (PLAYER->getRect().right > WINSIZE_X / 2 && _bm->getPosX() + 1280 < 2400)
        {
            _bm->setPosX(_bm->getPosX() + 4);
            PLAYER->setPosX(PLAYER->getPosX() - 4.0f);
            _bm->movdRect(4);
        }
        if (PLAYER->getLeft() && PLAYER->getCenterX() < WINSIZE_X / 2 + 10 && (_bm->getPosX() > 0))
        {
            _bm->setPosX(_bm->getPosX() - 4);
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
            _bm->movdRect(-4);
        }
    }

    if (_intro)
    {
        _cnt++;
        if (_cnt % 2 == 0)
        {
            if (_bm->getPosX() < 650)
            {
                _bm->setPosX(_bm->getPosX() + 8);
                PLAYER->setPosX(PLAYER->getPosX() - 8.0f);
                _bm->movdRect(8);
                _boss->setX(_boss->getX() - 8);
            }
        }
        _boss->update();
    }

    RECT _rt;
    if (PLAYER->getPosX() >= _bm->getRect().left)
    {
        _intro = true;
        PLAYER->setPosX(_bm->getRect().left);
        //PLAYER->getState().reset();
        PLAYER->setAction("IDLE");
    }

    for (int i = PLAYER->getRect().left; i <= PLAYER->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("BossMap_collision")->getMemDC(),
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
}

void BossStage::render(void)
{
    _bm->render(getMemDC());
    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());

    if (_intro)
        _boss->render(getMemDC());
}
