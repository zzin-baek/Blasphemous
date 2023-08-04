#pragma once
#include "GameNode.h"
#include "BossMap2.h"
#include "Pietat.h"

class BossStage2 : public GameNode
{
private:
	BossMap2* _bm;
	Pietat* _boss;

public:
	HRESULT init(void);
	void release(void);
	void update(void); 
	void render(void);

	BossStage2() {}
	~BossStage2() {}
};