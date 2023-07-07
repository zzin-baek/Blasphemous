#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:

	GameNode* _currentScene;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() : _currentScene(nullptr) {}
	~MainGame() {}

};