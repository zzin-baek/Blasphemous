#pragma once
#include "GameNode.h"
#include "MainMenu.h"

class MainGame : public GameNode
{
private:
	MainMenu* _mainMenu;

	GameNode* _currentScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}

};