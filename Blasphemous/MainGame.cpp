#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_mainMenu = new MainMenu;
	_mainMenu->init();

	_currentScene = _mainMenu;
	assert(_currentScene != nullptr);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();

	SAFE_DELETE(_mainMenu);
}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();
}

void MainGame::render(void)
{
	GameNode::render();
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	_currentScene->render();

	this->getBackBuffer()->render(getHDC());
}
