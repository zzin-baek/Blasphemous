#pragma once
#include "Enemy.h"

#define MAX_ROCK 10

struct tagRock
{
	POINTF pos;
	POINT idx;
	RECT rock;
	int cnt;
	float angle;
	bool shoot = false;
	bool broke = false;
	deque<char*> cycle;
};

struct stImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

class Stoner : public Enemy
{
private:
	POINTF _stonerPos;
	RECT _stoner, _attackBoundary;
	deque<char*> _stList;
	tagRock _rock[MAX_ROCK];
	bitset<4> _stState;
	map<string, stImageInfo> _sync;

	int _cnt, _hp;
	bool _isLeft, _isRising, _die, _hit, _isAttack;
	bool _onceRock;
	POINT _idx;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	HRESULT init(float locX, float locY);
	void initSync(void);
	void move(void);

	void rockMove(void);
	void rockCycle(void);
	void rockCollision(void);
	void setRockPos(int x, int y);

	void render(HDC hdc);

	inline float getPosX() { return _stonerPos.x; }
	inline float getPosY() { return _stonerPos.y; }
	inline void setPosX(float x) { _stonerPos.x = x; }
	inline void setPosY(float y) { _stonerPos.y = y; }

	bitset<4> getState() { return _stState; }
	void setState(int num, bool state) { _stState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }
	void addAction(char* _action) { _stList.push_back(_action); }

	RECT getBoundary() { return _attackBoundary; }
	RECT getRect() { return _stoner; }
	void setRising(bool state) { _isRising = state; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }
	bool getDie() { return _die; }

	bool isEmpty() { return _stList.empty(); }
	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	Stoner() {}
	~Stoner() {}
};

