#pragma once
#include "GameNode.h"
#include "BossMap2.h"
#include "Pietat.h"

class BossStage2 : public GameNode
{
private:
	BossMap2* _bm;
	Pietat* _boss;

	int _cnt, _nextStage;
	bool _once;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	inline int getNext() { return _nextStage; }

	BossStage2() {}
	~BossStage2() {}
};