#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	assert(_currentScene != nullptr, "MainGame 초기화 부분에서 노드 파트 오류 발생");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
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

	cout << "hi" << endl;

	this->getBackBuffer()->render(getHDC());
}
