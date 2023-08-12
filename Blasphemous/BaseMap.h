#pragma once
#include "GameNode.h"
#include "BattleField.h"
#include "Acolyte.h"
#include "Stoner.h"
#include "Shielder.h"
#include "Item.h"

// ������ �����ְ�, ������ ���� �� �ʰ��� ��ȣ�ۿ� ������ �����ֱ� ���� ��
class BaseMap : public GameNode
{
private:
	BattleField* _bf;
	Acolyte* _ac;
	Stoner* _st;
	Shielder* _sh;
	Item* _item;

	vector<Item*> _itemList;
	vector<Acolyte*> _acolyteList;
	vector<Stoner*> _stonerList;
	vector<Shielder*> _shielderList;

	bitset<5> _once;

	int _cnt, _nextStage, _preStage;
	bool _isInven;

	int _term;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }
	int getPre() { return _preStage; }
	void setPre(int p) { _preStage = p; }

	BaseMap() {}
	~BaseMap() {}
};

