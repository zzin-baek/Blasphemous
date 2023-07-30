#pragma once
#include "Enemy.h"

struct tagStone
{
	POINT pos;
	float angle;
	bool shoot = false;
	bool broke = false;
};

class Stoner : public Enemy
{
private:
	tagStone _stone[10];

public:
	HRESULT init(void);
	void move(void);
	void render(HDC hdc);

	Stoner() {}
	~Stoner() {}
};

