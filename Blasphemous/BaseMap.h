#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Acolyte.h"
#include "BattleField.h"
#include "Item.h"

// bitset: 기본, 걷기, 점프, 앉기, 매달리기
//typedef enum eState
//{
//	WALK,
//	JUMP,
//	CROUCH,
//	DODGE,
//	HANGON
//};

// 움직임 보여주고, 적과의 전투 및 맵과의 상호작용 동작을 보여주기 위한 맵
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

