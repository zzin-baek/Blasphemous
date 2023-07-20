#pragma once
#include "GameNode.h"
#include "BossMap.h"
#include "Player.h"
#include "Isidora.h"

class BossStage : public GameNode
{
private:
	BossMap* _bm;
	Player* _pl;
	Isidora* _boss;
	
	RECT _startPos;
	bool _intro;
	int _cnt;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossStage() {}
	~BossStage() {}
};

