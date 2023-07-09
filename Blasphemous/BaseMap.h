#pragma once
#include "GameNode.h"
#include "Player.h"
#include "BattleField.h"

// 움직임 보여주고, 적과의 전투 및 맵과의 상호작용 동작을 보여주기 위한 맵
class BaseMap : public GameNode
{
private:
	Player* _pl;
	BattleField* _bf;

	int _cnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BaseMap() {}
	~BaseMap() {}
};

