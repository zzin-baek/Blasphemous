#pragma once

enum eSkill
{
	RISING,
	TWIRL,
	SLASH
};

struct POINTF
{
	float x;
	float y;
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

class Isidora
{
private:
	POINTF _pos, _test, _plPos;
	POINT _idx;
	deque<char*> _pattern;
	map<char*, tagBoss> _sync;

	tagColumn _cl[7];
	tagFireBall _fb[10];

	RECT _isidora, _box, _mask;
	int _cnt, _hp, _patternNum;
	int _interval;
	char _strSkill[128];
	float tempX, tempY;

	bool _isLeft, _finIntro, _doNothing, _once;
	char _loc[128];

public:
	HRESULT init(void);
	void initSync(void);
	void initPos(float x, float y) { _pos.x = x; _pos.y = y; }
	void update(void);
	void useSkill(void);

	void columnCreate(void);
	void columnCycle(void);

	void fireBallCreate(void);
	void fireBallMove(void);
	void fireBallCycle(void);

	void render(HDC hdc);

	inline float getX() { return _pos.x; }
	inline float getY() { return _pos.y; }
	inline void setX(float x) { _pos.x = x; }
	inline void setY(float y) { _pos.y = y; }

	inline void setIdxX(int x) { _idx.x = x; }
	inline void setIdxY(int y) { _idx.y = y; }

	inline bool getLeft() { return _isLeft; }
	inline bool getFin() { return _finIntro; }
	inline bool getDo() { return _doNothing; }
	inline void setDo(int state) { _doNothing = state; }
	inline void setOnce(bool state) { _once = state; }

	inline void setPattern(int pattern) { _patternNum = pattern; }

	inline RECT getBoss() { return _isidora; }

	void addPattern(char* action) 
	{ 
		wsprintf(_strSkill, action);
		_pattern.push_back(action); 
	}

	Isidora() {}
	~Isidora() {}
};

