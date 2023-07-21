#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	//PLAYER->init(88, 484);

	_mainMenu = new MainMenu;
	_mainMenu->init();

	_tutorial = new Tutorial;
	_tutorial->init();

	_baseMap = new BaseMap;
	_baseMap->init();

	_bossStage = new BossStage;
	_bossStage->init();

	_currentScene = _mainMenu;
	assert(_currentScene != nullptr);

	for (int i = 0; i < 4; i++)
		_initOnce[i] = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_mainMenu);
	SAFE_DELETE(_tutorial);
	SAFE_DELETE(_baseMap);
}

void MainGame::update(void)
{
	GameNode::update();

	if (_mainMenu->getSelect() == 1)
	{
		if (!_initOnce[0])
		{
			PLAYER->init(88, 484);
			_initOnce[0] = true;
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
		}
		_currentScene = _baseMap;
	}

	if (_baseMap->getNext())
	{
		if (!_initOnce[2])
		{
			PLAYER->init(88, 484);
			_initOnce[2] = true;
		}
		_currentScene = _bossStage;
	}
	else if (_baseMap->getPre())
	{
		if (!_initOnce[3])
		{
			PLAYER->init(1200, 484);
			_initOnce[3] = true;
			_initOnce[1] = false;
			_tutorial->setNext(0);
		}
		_currentScene = _tutorial;
	}
	cout << _tutorial->getNext() << endl;
	cout << "getNExt" << _baseMap->getNext() << endl;
	cout << "getpre" << _baseMap->getPre() << endl;
	_currentScene->update();
}

void MainGame::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}
