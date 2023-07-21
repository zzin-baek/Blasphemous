#pragma once
#include "GameNode.h"
//#include "Player.h"
#include "TutorialField.h"
#include "Item.h"

class Tutorial : public GameNode
{
private:
	//Player* _pl;
	TutorialField* _tf;
	Item* _item;

	vector<Item*> _itemList;

	int _nextStage;
	bool _isInven;

public:
	HRESULT init(void);
	void init(int s, int e);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }
	void setNext(int n) { _nextStage = n; }

	Tutorial() {}
	~Tutorial() {}
};

