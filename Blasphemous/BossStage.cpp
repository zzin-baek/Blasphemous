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

    _once = false;

    for (int i = 0; i < 6; i++)
        _phase1[i] = i + 1;
    for (int i = 0; i < 3; i++)
        _phase2[i] = i + 7;

    _sq.push_back(11);
    _sq.push_back(12);
    _sq.push_back(11);
    _sq.push_back(12);
    _sq.push_back(13);

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

        if (PLAYER->getHitBox().left <= 0)
            PLAYER->setPosX(PLAYER->getPosX() + 4.0f);
    }

    if ((!_intro || _ending) && !_mainStage)
    {
        // 카메라
        if (PLAYER->getHitBox().right > WINSIZE_X / 2 && _bm->getPosX() + 1280 < 2400)
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
            //_boss->addPattern("Isidora_Intro2");
            _boss->addPattern("Isidora_idle");
            _boss->addPattern("Isidora_vanish");

            if (_boss->getLeft())
                _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_idle")->getMaxFrameX());
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
            int _temp;
     
            if (_boss->getPhase() == 1 && _boss->getHP() > 200)
                _pattern = RND->getIntArray(_phase1, 6);
            else if (_boss->getHP() <= 200 && !_boss->getIsPhase())
            {
                _pattern = _sq[0];
                _sq.erase(_sq.begin());
            }
            else if (_boss->getPhase() == 2)
                _pattern = RND->getIntArray(_phase2, 3);
            else
                _pattern = 10;

            _boss->setLeft(RND->getInt(2));
            _boss->setPattern(_pattern);
            switch (_pattern)
            {
            case 1:
            case 2:
                _boss->setDo(false);
                break;
            case 3:
                _boss->initPos(WINSIZE_X / 2 - 10, WINSIZE_Y / 2 + 100);
                _boss->addPattern("Isidora_outToCast");
                _boss->addPattern("Isidora_cast");
                _boss->addPattern("Isidora_vanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToCast")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_outToCast")->getMaxFrameX() } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 1, { 11, IMAGEMANAGER->findImage("Isidora_cast")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX() } });

                _boss->setDo(false);
                break;
            case 4: // 올려치기
                if (_boss->getLeft())
                    _boss->initPos(1100, 600);
                else
                    _boss->initPos(200, 600);

                _boss->addPattern("Isidora_sparkAppear");
                _boss->addPattern("Isidora_sparkLoop");
                _boss->addPattern("Isidora_outToRising");
                _boss->addPattern("Isidora_scy2");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_vanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_sparkAppear")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_sparkAppear")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_sparkLoop")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToRising")->getMaxFrameX()} });
                _boss->addSeq({ 1, {20, IMAGEMANAGER->findImage("Isidora_scy2")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;
            case 5:
                _boss->initPos(1000, 400);
                _boss->addPattern("Isidora_outToTwirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_slash");
                _boss->addPattern("Isidora_screen_slash");
                _boss->addPattern("Isidora_screenslash_effect");
                _boss->addPattern("Isidora_risingAppear");
                _boss->addPattern("Isidora_screen_slash");
                _boss->addPattern("Isidora_screenslash_effect");
                _boss->addPattern("Isidora_risingAppear");
                _boss->addPattern("Isidora_screen_slash");
                _boss->addPattern("Isidora_screenslash_effect");
                _boss->addPattern("Isidora_slashToVanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, 22 } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screen_slash")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screenslash_effect")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_risingAppear")->getMaxFrameX()} });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screen_slash")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screenslash_effect")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_risingAppear")->getMaxFrameX()} });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screen_slash")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_screenslash_effect")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_slashToVanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;
            case 6: // 회오리감자
                _temp = RND->getFromIntTo(150, 1140);
                _boss->initPos(_temp, 500);

                if (_temp <= PLAYER->getHitBox().left)
                    _boss->setLeft(false);
                else
                    _boss->setLeft(true);

                _boss->addPattern("Isidora_outToTwirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_slash");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_slash");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_vanish");


                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_slash")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {8, IMAGEMANAGER->findImage("Isidora_slash")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;

            // 페이즈 2
            case 7:
                if (_boss->getLeft())
                    _boss->initPos(1050, 450);
                else
                    _boss->initPos(200, 450);

                _boss->addPattern("Isidora_outToRising");
                _boss->addPattern("Isidora_scy2");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_vanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToRising")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToRising")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0,  IMAGEMANAGER->findImage("Isidora_scy2")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0,  IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0,  IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0,  IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;
            case 8:
                _temp = RND->getFromIntTo(150, 1140);
                _boss->initPos(_temp, 500);

                if (_temp <= PLAYER->getHitBox().left)
                    _boss->setLeft(false);
                else
                    _boss->setLeft(true);

                _boss->addPattern("Isidora_outToTwirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_slash");
                _boss->addPattern("Isidora_twirlToVanish");

                
                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_slash")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirlToVanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;
            case 9:
                _temp = RND->getFromIntTo(150, 1100);
                _boss->initPos(_temp, 500);

                if (_temp <= PLAYER->getHitBox().left)
                    _boss->setLeft(false);
                else
                    _boss->setLeft(true);

                _boss->addPattern("Isidora_outToTwirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_slash");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_scy");
                _boss->addPattern("Isidora_twirl");
                _boss->addPattern("Isidora_backToIdle");
                _boss->addPattern("Isidora_vanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToTwirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_slash")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_scy")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 0, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_twirl")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_backToIdle")->getMaxFrameX()} });
                _boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX()} });

                _boss->setDo(false);
                break;
            case 10:
                if (!_once)
                {
                    _boss->initPos(WINSIZE_X / 2 - 100, WINSIZE_Y / 2);
                    _once = true;
                }            
                _boss->setLeft(true);

                //_boss->addPattern("Isidora_outToCast");
                _boss->addPattern("Isidora_cast");

                //_boss->addSeq({ 1, {0, IMAGEMANAGER->findImage("Isidora_outToCast")->getMaxFrameX() } });
                _boss->addSeq({ 0, { 11, 21 } });

                _boss->setDo(false);
                break;
            case 11:
            case 12:
                _boss->setDo(false);
                break;
            case 13:
                _boss->initPos(WINSIZE_X / 2 - 10, WINSIZE_Y / 2 + 100);
                _boss->addPattern("Isidora_outToCast");
                _boss->addPattern("Isidora_cast");
                _boss->addPattern("Isidora_vanish");

                if (_boss->getLeft())
                    _boss->setIdxX(IMAGEMANAGER->findImage("Isidora_outToCast")->getMaxFrameX());
                else
                    _boss->setIdxX(0);

                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_outToCast")->getMaxFrameX() } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 0, { 11, 21 } });
                _boss->addSeq({ 1, { 11, IMAGEMANAGER->findImage("Isidora_cast")->getMaxFrameX() } });
                _boss->addSeq({ 1, { 0, IMAGEMANAGER->findImage("Isidora_vanish")->getMaxFrameX() } });

                _boss->setDo(false);
                break;
            }
            cout << "패턴 넘버" << _pattern << endl;
        }        
    }

    if (_boss->getIsPhase() && _bm->getScene() < WINSIZE_X / 2)
    {
        _bm->setScene(_bm->getScene() + 1);
        if (_bm->getScene() > 100)
            _bm->changeBrazier("Brazier_HalfLoop");
        if (_bm->getScene() > 200)
            _bm->changeBrazier("Brazier_HalfToFull");
        if (_bm->getScene() > 230)
            _bm->changeBrazier("Brazier_FullLoop");
    }

    _boss->update();
    _bm->update();

    for (int i = PLAYER->getHitBox().left; i <= PLAYER->getHitBox().right; i++)
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

    if (IntersectRect(&_rt, &_boss->getHitBox(), &PLAYER->getHitBox())
        && PLAYER->getState()[PARRY])// && _boss->isAttack())
    {
        PLAYER->setParry(true);

    }
    else if (IntersectRect(&_rt, &_boss->getHitBox(), &PLAYER->getHitBox())
        && !PLAYER->getState()[PARRY])
    {
        if (!PLAYER->getState()[HIT] && !PLAYER->getHit())// && _shielderList[0]->isAttack())
        {
            PLAYER->setHit(true);
            PLAYER->setHP(PLAYER->getHP() - 5);
        }
    }

    if (IntersectRect(&_rt, &_boss->getHitBox(), &PLAYER->getRect()) && PLAYER->getState()[ATTACK])
    {
        if (!_boss->getState()[HIT_BOSS])
        {
            _boss->setState(HIT_BOSS, true);

            _boss->setHP(_boss->getHP() - 10);
        }
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