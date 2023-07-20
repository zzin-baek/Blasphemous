#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Acolyte.h"
#include "BattleField.h"
#include "Item.h"

// bitset: �⺻, �ȱ�, ����, �ɱ�, �Ŵ޸���
//typedef enum eState
//{
//	WALK,
//	JUMP,
//	CROUCH,
//	DODGE,
//	HANGON
//};

// ������ �����ְ�, ������ ���� �� �ʰ��� ��ȣ�ۿ� ������ �����ֱ� ���� ��
class BaseMap : public GameNode
{
private:
	Player* _pl;
	Acolyte* _ac;
	BattleField* _bf;
	Item* _item;

	vector<Item*> _itemList;
	vector<Acolyte*> _acolyteList;

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

	BaseMap() {}
	~BaseMap() {}
};

