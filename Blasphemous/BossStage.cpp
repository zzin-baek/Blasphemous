#include "Stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init(void)
{
    _bm = new BossMap;
    _bm->init();

    _boss = new Isidora;
    _boss->init();

    _startPos = RectMakeCenter(490, 490, 50, 60);
    _intro = _mainStage = _ending = false;
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

        if (PLAYER->getRect().left <= 0)
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
    }

    if ((!_intro || _ending) && !_mainStage)
    {
        // 카메라
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

    // 계속해서 인트로 해결하기 
    RECT _rt;
    if (PLAYER->getPosX() >= _bm->getRect().left && !_boss->getFin())
    {
        _intro = true;
        PLAYER->setPosX(_bm->getRect().left);
        PLAYER->getState().reset();
        PLAYER->setAction("IDLE");
    }

    if (_intro)
    {
        _cnt++;
        if (_cnt == 1)
        {
            //_ac = "Isidora_Intro2";
            _boss->addPattern("Isidora_Intro2");
            _boss->addPattern("Isidora_idle");
            _boss->addPattern("Isidora_vanish");

            if (_boss->getLeft())
                _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_Intro2")->getMaxFrameX());
            else
                _boss->setIdxX(0);
        }
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

        if (_boss->getFin())
        {
            _intro = false;
            _mainStage = true;
        }
    }

    if (_mainStage)
    {
        if (_boss->getDo())
        {
            //_boss->setOnce(false);
            _pattern = RND->getFromIntTo(1, 2);
            _boss->setPattern(_pattern);
            switch (_pattern)
            {
            case 1:
                //_boss->initPos(200, 200);
                //_boss->addPattern("Isidora_outToCast");
                //_boss->addPattern("Isidora_slash");
                //_boss->addPattern("Isidora_slashToVanish");
                _boss->setDo(false);
                break;
            case 2:
                //_boss->initPos(1000, 400);
                //_boss->addPattern("Isidora_outToRising");
                //_boss->addPattern("Isidora_scy_crop");
                //_boss->addPattern("Isidora_vanish");
                _boss->setDo(false);
                break;
            case 3:
                //_boss->initPos(400, 100);
                //_boss->addPattern("Isidora_outToTwirl");
                //_boss->addPattern("Isidora_twirl");
                //_boss->addPattern("Isidora_twirlToVanish");
                _boss->setDo(false);
                break;
            case 4:
                //_boss->initPos(WINSIZE_X/2, 300);
                //_boss->addPattern("Isidora_outToCast");
                //_boss->addPattern("Isidora_cast");
                //_boss->addPattern("Isidora_vanish");
                _boss->setDo(false);
                break;
            }
            cout << "패턴 넘버" << _pattern << endl;
        }
    }

    _boss->update();
    _bm->update();

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
    
    if (_intro || _mainStage)
        _boss->render(getMemDC());
    
    PLAYER->renderPlayer(getMemDC());
    PLAYER->renderProfile(getMemDC());
}

// vector<tagColumn> _column;