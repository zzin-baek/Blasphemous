#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TutorialField.h"

class Tutorial : public GameNode
{
private:
	Player* _pl;
	TutorialField* _tf;

	int _nextStage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }

	Tutorial() {}
	~Tutorial() {}
};

