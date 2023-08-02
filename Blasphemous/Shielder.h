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
	RECT _shielder, _attack;
	RECT _attackBoundary[2];
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
	void attack(void);
	void render(HDC hdc);

public:
	inline float getPosX() { return _shielderPos.x; }
	inline float getPosY() { return _shielderPos.y; }
	inline void setPosX(float x) { _shielderPos.x = x; }
	inline void setPosY(float y) { _shielderPos.y = y; }

	void setX(int x) { _idx.x = x; }
	void setY(int y) { _idx.y = y; }

	inline void setLeft(bool state) { _isLeft = state; }
	inline bool getLeft() { return _isLeft; }
	inline bool isAttack() { return _isAttack; }
	inline void setAttack(bool state) { _isAttack = state; }
	inline bool getDie() { return _die; }

	bitset<4> getState() { return _shState; }
	void setState(int num, bool state) { _shState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }
	char* getAction() { return _strAction; }

	RECT getRect() { return _shielder; }
	RECT getBoundary(int num) { return _attackBoundary[num]; }
	RECT getAttack() { return _attack; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	bool isEmpty() { return _shList.empty(); }
	void resetState() { _shState.reset(); }
	void clearAll() { _shList.clear(); }
	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }
	void addAction(char* _action) { _shList.push_back(_action); }

};

