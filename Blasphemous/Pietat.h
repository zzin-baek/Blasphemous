#pragma once

#define MAX_THORN 10
#define MAX_SPIT 5

enum ePietat
{
	ATTACK_PIETAT = 0,
	HIT_PIETAT,
	DIE_PIETAT
};

struct tagThorn
{
	POINTF _center;
	POINT _idx;
	RECT _proj;
	int _cnt;
	bool _create = false;
	bool _fire = false;
};

struct tagSpit
{
	POINTF _center;
	POINT _idx;
	RECT _proj;
	int _cnt;
	int _state = 0;
	float angle;
	bool _create = false;
	bool _destroy = false;
	deque<char*> _cycle;
};

struct tagPietat
{
	int timing;
	POINT left;
	POINT right;
};

class Pietat
{
private:
	POINTF _pos, _center, _plPos;
	POINT _idx, _introIdx;

	deque<char*> _pattern;
	map<string, tagPietat> _sync;
	bitset<3> _ptState;

	tagThorn _thorn[MAX_THORN];
	tagSpit _spit[MAX_SPIT];

	RECT _pietat, _hitBox, _attack;
	int _cnt, _phase, _patternNum, _hp, _dist;
	int _introIndex, _doNothing, _intervalT;
	float _temp;
	bool _isLeft, _intro, _outro, _finIntro, _finOutro;
	bool _onceThorn, _isAttack, _hit;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	void initSync(void);
	void update(void);

	void useSkill(void);
	void attack(void);

	void thornCreate(void);
	void thornCycle(void);
	
	void spitState(void);
	void spitCycle(void);
	void spitMove(void);

	void setProjectilePos(int x);
	void projectileCollision(void);

	void showIntro(void);
	void render(HDC hdc);
	void renderHP(HDC hdc);

public:
	inline void setIntro(bool state) { _intro = state; }
	inline void setOutro(bool state) { _outro = state; }
	inline bool getIntro() { return _intro; }
	inline bool getOutro() { return _outro; }

	inline void setX(int x) { _pos.x = x; }
	inline void setY(int y) { _pos.y = y; }
	inline int getX() { return _pos.x; }
	inline int getY() { return _pos.y; }

	inline bool isEmpty() { return _pattern.empty(); }

	inline void setAction(char* action) { wsprintf(_strAction, action); }
	inline char* getAction() { return _strAction; }

	inline RECT getBoss() { return _pietat; }
	inline RECT getHitBox() { return _hitBox; }
	inline RECT getAttack() { return _attack; }

	inline int getHP() { return _hp; }
	inline void setHP(int hp) { _hp = hp; }

	inline bitset<3> getState() { return _ptState; }
	inline void setState(int num, bool state) { _ptState.set(num, state); }
	inline bool isAttack() { return _isAttack; }
};

