#pragma once
#include "GameNode.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "BaseMap.h"

class MainGame : public GameNode
{
private:
	MainMenu* _mainMenu;
	Tutorial* _tutorial;
	BaseMap* _baseMap;

	GameNode* _currentScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}

};