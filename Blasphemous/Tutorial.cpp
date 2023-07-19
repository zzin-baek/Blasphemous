#include "Stdafx.h"
#include "Tutorial.h"

HRESULT Tutorial::init(void)
{
    _pl = new Player();
    _pl->init(88, 484);

    _tf = new TutorialField();
    _tf->init();

    _nextStage = 0;


    return S_OK;
}

void Tutorial::release(void)
{
    SAFE_DELETE(_pl);
    SAFE_DELETE(_tf);
}

void Tutorial::update(void)
{
    _pl->playerAction();
    _pl->playerMove();

    if (!_pl->getGround())
        _pl->setPosY(_pl->getPosY() + 5.0f);

    for (int i = _pl->getRect().left; i <= _pl->getRect().right; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("tutorial_map_collision")->getMemDC(),
            i, _pl->getRect().bottom);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if ((r == 255 && g == 0 && b == 255))
        {
            _pl->setGround(true);
            break;
        }
        _pl->setGround(false);
    }

    if (_pl->getCenterX() > WINSIZE_X)
        _nextStage = 1;
}

void Tutorial::render(void)
{
    _tf->render(getMemDC());
    _pl->renderPlayer(getMemDC());
    _pl->renderProfile(getMemDC());
}
