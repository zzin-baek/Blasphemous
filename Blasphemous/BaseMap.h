#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Acolyte.h"
#include "BattleField.h"

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

