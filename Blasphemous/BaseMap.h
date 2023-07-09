#pragma once
#include "GameNode.h"
#include "Player.h"
#include "BattleField.h"

// ������ �����ְ�, ������ ���� �� �ʰ��� ��ȣ�ۿ� ������ �����ֱ� ���� ��
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

