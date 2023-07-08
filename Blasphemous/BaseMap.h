#pragma once
#include "GameNode.h"


// 움직임 보여주고, 적과의 전투 및 맵과의 상호작용 동작을 보여주기 위한 맵
class BaseMap : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BaseMap() {}
	~BaseMap() {}
};

