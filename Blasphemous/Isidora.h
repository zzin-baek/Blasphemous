#pragma once

#define MAX_COLUMN 12
#define MAX_FIREBALL 15

enum eBossState
{
	ATTACK_BOSS = 0,
	HIT_BOSS,
	DIE_BOSS
};
struct tagBoss
{
	int timing;
	POINT left;
	POINT right;
};

struct tagFireBall
{
	POINTF _center;
	POINT _idx;
	int _cnt;
	float _angle;
	bool _fire = false;
	bool _create = false;
	bool _trace = false;
	bool _visible = true;
	deque<char*> _cycle;
};

struct tagColumn
{
	POINTF _clPos;
	POINT _idx;
	int _cnt;
	bool _fire = false;
	bool _create = false;
	deque<char*> _cycle;
};

// sequence����
struct tagSequence
{
	bool _pass;
	POINT _current;
};

class Isidora
{
private:
	POINTF _pos, _center, _plPos;
	POINTF _temp, _risingSpot[3];
	POINT _idx;

	deque<char*> _pattern;
	map<char*, tagBoss> _sync;
	vector<tagSequence> _seq;
	bitset<3> _idState;

	tagColumn _cl[MAX_COLUMN];
	tagFireBall _fb[MAX_FIREBALL];

private:
	RECT _isidora, _hitBox, _mask;
	int _cnt, _hp, _phase, _intervalC, _intervalF, _patternNum;

	bool _isLeft, _finIntro, _isPhase2, _isAttack, _doNothing;
	bool _once, _once2, _onceColumn, _onceFire;

	char _loc[128];

public:
	HRESULT init(void);
	void initSync(void);
	void initPos(float x, float y) { _pos.x = x; _pos.y = y; }
	void update(void);
	void useSkill(void);

	void bossDeath(void);
	void switchPhase(void);

	void columnInit(int num, int interval);
	void columnCreate(void);
	void columnCycle(void);
	void columnCycle(bool phase);

	void fireBallCreate(void);
	void fireBallMove(void);
	void fireBallCycle(void);

	void render(HDC hdc);

public:
	inline float getX() { return _pos.x; }
	inline float getY() { return _pos.y; }
	inline void setX(float x) { _pos.x = x; }
	inline void setY(float y) { _pos.y = y; }

	inline void setIdxX(int x) { _idx.x = x; }
	inline void setIdxY(int y) { _idx.y = y; }

	inline bool getLeft() { return _isLeft; }
	inline void setLeft(bool state) { _isLeft = state; }
	inline bool getFin() { return _finIntro; }
	inline bool getDo() { return _doNothing; }
	inline void setDo(int state) { _doNothing = state; }

	inline int getPhase() { return _phase; }
	inline bool getIsPhase() { return _isPhase2; }
	inline int getHP() { return _hp; }
	inline void setHP(int hp) { _hp = hp; }

	inline void setPattern(int pattern) { _patternNum = pattern; }
	inline void addSeq(tagSequence seq) { _seq.push_back(seq); }

	inline RECT getBoss() { return _isidora; }
	inline RECT getHitBox() { return _hitBox; }
	inline bitset<3> getState() { return _idState; }
	inline void setState(int num, bool state) { _idState.set(num, state); }
	inline bool isAttack() { return _isAttack; }

	void addPattern(char* action) { _pattern.push_back(action); }

	Isidora() {}
	~Isidora() {}
};