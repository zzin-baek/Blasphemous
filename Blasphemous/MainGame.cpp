#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_mainMenu = new MainMenu;
	_mainMenu->init();

	_tutorial = new Tutorial;
	_tutorial->init();

	_baseMap = new BaseMap;
	_baseMap->init();

	_teleport = new Teleport;
	_teleport->init();

	_bossStage = new BossStage;
	_bossStage->init();

	_bossStage2 = new BossStage2;
	_bossStage2->init();

	_currentScene = _mainMenu;
	assert(_currentScene != nullptr);

	for (int i = 0; i < 6; i++)
		_initOnce[i] = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_mainMenu);
	SAFE_DELETE(_tutorial);
	SAFE_DELETE(_baseMap);
	SAFE_DELETE(_teleport);
	SAFE_DELETE(_bossStage);
	SAFE_DELETE(_bossStage2);
}

void MainGame::update(void)
{
	GameNode::update();
	EFFECT->updateEffect();

	if (_mainMenu->getSelect() == 1)
	{
		if (!_initOnce[0])
		{
			PLAYER->init(WINSIZE_X / 2 - 100, 480);
			_initOnce[0] = true;

			SOUNDMANAGER->stopMp3WithKey("OPENING");
			SOUNDMANAGER->playSoundWithKey("zone");
		}
		_currentScene = _tutorial;
	}
	else if (_mainMenu->getSelect() == 2)
		PostMessage(_hWnd, WM_DESTROY, 0, 0);


	if (_tutorial->getNext())
	{
		if (!_initOnce[1])
		{
			PLAYER->init(10, 330);
			_initOnce[1] = true;
			_initOnce[3] = false;
			_baseMap->setPre(0);

			SOUNDMANAGER->playSoundWithKey("churches_field");
		}
		_currentScene = _baseMap;
	}

	if (_baseMap->getNext())
	{
		if (!_initOnce[2])
		{
			PLAYER->init(88, 484);
			_initOnce[2] = true;
			SOUNDMANAGER->stopMp3WithKey("churches_field");
		}
		_currentScene = _teleport;
	}
	else if (_baseMap->getPre())
	{
		if (!_initOnce[3])
		{
			PLAYER->init(1200, 484);
			_initOnce[3] = true;
			_initOnce[1] = false;
			_tutorial->setNext(0);

			SOUNDMANAGER->stopMp3WithKey("churches_field");
		}
		_currentScene = _tutorial;
	}

	if (_teleport->getNext())
	{
		if (!_initOnce[4])
		{
			PLAYER->init(900, 430);
			_initOnce[4] = true;
			SOUNDMANAGER->playSoundWithKey("pietat_breath");
		}
		_currentScene = _bossStage2;
	}

	if (_bossStage2->getNext())
	{
		if (!_initOnce[5])
		{
			PLAYER->init(88, 484);
			_initOnce[5] = true;
		}
		_currentScene = _bossStage;
	}

	_currentScene->update();
}

void MainGame::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_currentScene->render();
	EFFECT->renderEffect(getMemDC());

	this->getBackBuffer()->render(getHDC());
}
