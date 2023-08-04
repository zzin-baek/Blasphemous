#pragma once
#include "GameNode.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "BaseMap.h"
#include "BossStage.h"
#include "BossStage2.h"

class MainGame : public GameNode
{
private:
	MainMenu* _mainMenu;
	Tutorial* _tutorial;
	BaseMap* _baseMap;
	BossStage* _bossStage;
	BossStage2* _bossStage2;

	GameNode* _currentScene;

	bool _initOnce[5];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}

};