#pragma once
#include "Enemy.h"

struct acImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

class Acolyte : public Enemy
{
private:
	POINT _acolytePos;
	RECT _acolyte, _attack;
	RECT _attackBoundary[2];
	deque<string> _acList;
	bitset<4> _acState;
	map<string, acImageInfo> _sync;

	bool _isLeft, _canAttack, _hit, _die;
	int _cnt, _idx_x, _idx_y;
	int _hp;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	void initSync(void);
	void move(void);
	void attack(void);
	
	void render(HDC hdc);

	void setPosX(int x) { _acolytePos.x = x; }
	void setPosY(int y) { _acolytePos.y = y; }
	int getPosX() { return _acolytePos.x; }
	int getPosY() { return _acolytePos.y; }

	void setX(int x) { _idx_x = x; }
	void setY(int y) { _idx_y = y; }

	void setLeft(bool state) { _isLeft = state; }
	bool getLeft() { return _isLeft; }
	bool canAttack() { return _canAttack; }
	bool getDie() { return _die; }

	bitset<4> getState() { return _acState; }
	void setState(int num, bool state) { _acState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }

	RECT getRect() { return _acolyte; }
	RECT getBoundary(int num) { return _attackBoundary[num]; }
	RECT getAttack() { return _attack; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	bool isEmpty() { return _acList.empty(); }
	void addAction(string _action) { _acList.push_back(_action); }

	Acolyte() {}
	~Acolyte() {}
};