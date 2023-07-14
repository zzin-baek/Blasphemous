#pragma once
#include "Enemy.h"

class Acolyte : public Enemy
{
private:
	POINT _acolytePos;
	RECT _acolyte;
	RECT _attackBoundary[2];
	bitset<3> _acState;

	bool _isLeft;
	int _cnt, _idx_x, _idx_y;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	void move(void);
	void render(HDC hdc);

	void setPosX(int x) { _acolytePos.x = x; }
	void setPosY(int y) { _acolytePos.y = y; }
	int getPosX() { return _acolytePos.x; }
	int getPosY() { return _acolytePos.y; }

	void setLeft(bool state) { _isLeft = state; }
	bool getLeft() { return _isLeft; }

	void setState(int num, bool state) { _acState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }
	RECT getBoundary(int num) { return _attackBoundary[num]; }

	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	Acolyte() {}
	~Acolyte() {}
};