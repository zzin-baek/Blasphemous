#pragma once
#include "GameNode.h"
#include "BossMap.h"
#include "Isidora.h"

class BossStage : public GameNode
{
private:
	BossMap* _bm;
	Isidora* _boss;
	
	RECT _startPos;
	bool _intro, _mainStage, _ending;
	int _cnt, _pattern;
	char* _ac;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BossStage() {}
	~BossStage() {}
};

