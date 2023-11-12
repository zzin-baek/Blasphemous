#pragma once
#include "Enemy.h"

class Acolyte : public Enemy
{
private:
	POINTF _acolytePos;
	RECT _acolyte, _attack;
	RECT _attackBoundary[2];
	deque<char*> _acList;
	bitset<MAX_ENEMY_STATE> _acState;
	map<string, emImageInfo> _sync;

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

public:
	inline void setPosX(int x) { _acolytePos.x = x; }
	inline void setPosY(int y) { _acolytePos.y = y; }
	inline float getPosX() { return _acolytePos.x; }
	inline float getPosY() { return _acolytePos.y; }

	inline void setX(int x) { _idx_x = x; }
	inline void setY(int y) { _idx_y = y; }

	void setLeft(bool state) { _isLeft = state; }
	bool getLeft() { return _isLeft; }
	bool canAttack() { return _canAttack; }

	bitset<MAX_ENEMY_STATE> getState() { return _acState; }
	void setState(int num, bool state) { _acState.set(num, state); }
	void setAction(char* _action) { wsprintf(_strAction, _action); }
	void addAction(char* _action) { _acList.push_back(_action); }

	RECT getRect() { return _acolyte; }
	RECT getBoundary(int num) { return _attackBoundary[num]; }
	RECT getAttack() { return _attack; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }
	bool getDie() { return _die; }

	bool isEmpty() { return _acList.empty(); }
	void clearAll() { _acList.clear(); }

	int getMaxFrame() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }
	
	Acolyte() {}
	~Acolyte() {}
};