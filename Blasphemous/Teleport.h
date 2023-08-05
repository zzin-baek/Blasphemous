#pragma once
#include "GameNode.h"

class Teleport : public GameNode
{
private:
	POINT _pos, _idx;
	RECT _sceneStart;
	int _cnt, _ind, _alpha, _nextStage;
	bool _inPortal;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getNext() { return _nextStage; }

	Teleport() {}
	~Teleport() {}
};