#pragma once
#include "GameNode.h"
#include "Player.h"
#include "TutorialField.h"
#include "Item.h"

class Tutorial : public GameNode
{
private:
	Player* _pl;
	TutorialField* _tf;
	Item* _item;

	vector<Item*> _itemList;

	int _nextStage;
	bool _isInven;

public:
	HRESULT init(void);
	void initPlayer(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }

	Tutorial() {}
	~Tutorial() {}
};

