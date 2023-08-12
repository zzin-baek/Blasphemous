#pragma once
#include "GameNode.h"
#include "TutorialField.h"
#include "Item.h"

class Tutorial : public GameNode
{
private:
	TutorialField* _tf;
	Item* _item;

	vector<Item*> _itemList;

	int _nextStage;
	float _temp;
	bool _isInven, _isRespawn, _once;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }
	void setNext(int n) { _nextStage = n; }

	Tutorial() {}
	~Tutorial() {}
};

