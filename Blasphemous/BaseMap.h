#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Acolyte.h"
#include "BattleField.h"

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

	int _cnt;
	bool _isGround;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BaseMap() {}
	~BaseMap() {}
};

