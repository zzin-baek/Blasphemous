#pragma once

struct tagThorn
{
	POINTF _center;
	POINT _idx;
	int _cnt;
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
	POINT _idx;

	deque<char*> _pattern;
	map<char*, tagPietat> _sync;
	bitset<3> _ptState;

	RECT _pietat, _hitBox, _attack;

	char _strAction[128];
	char _loc[128];

public:
	HRESULT init(void);
	void initSync(void);
	void update(void);
	void useSkill(void);
	void render(HDC hdc);


public:


};

