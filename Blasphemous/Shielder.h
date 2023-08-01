#pragma once
#include "Enemy.h"

struct shImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

class Shielder : public Enemy
{
private:
	POINTF _shielderPos;
	RECT _shielder, _attackBoundary;
	deque<char*> _shList;
	bitset<4> _shState;
	map<string, shImageInfo> _sync;

	int _cnt, _hp;
	bool _isLeft, _die, _hit, _isAttack;
	POINT _idx;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	HRESULT init(float locX, float locY);
	void initSync(void);
	void move(void);
	void render(HDC hdc);

public:
	inline float getPosX() { return _shielderPos.x; }
	inline float getPosY() { return _shielderPos.y; }
	inline void setPosX(float x) { _shielderPos.x = x; }
	inline void setPosY(float y) { _shielderPos.y = y; }

	inline void setLeft(bool state) { _isLeft = state; }
	inline bool getLeft() { return _isLeft; }
	inline bool isAttack() { return _isAttack; }
	inline bool getDie() { return _die; }

	bitset<4> getState() { return _shState; }
	void setState(int num, bool state) { _shState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }

	RECT getRect() { return _shielder; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	bool isEmpty() { return _shList.empty(); }
	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }
	void addAction(char* _action) { _shList.push_back(_action); }

};

