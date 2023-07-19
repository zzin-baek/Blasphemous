#pragma once
#include "GameNode.h"
#include "BossMap.h"
#include "Player.h"

class BossStage : public GameNode
{
private:
	BossMap* _bm;
	Player* _pl;
	//Isidora* _boss;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossStage() {}
	~BossStage() {}
};

