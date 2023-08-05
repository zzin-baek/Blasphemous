#pragma once
#include "SingletonBase.h"

struct tagEffect
{
	char* _effect;
	int _cnt;
	POINT _pos;
	POINT _idx;
};

class Effect : public SingletonBase <Effect>
{
private:
	vector<tagEffect> _plEffect;
	vector<tagEffect> _bossEffect;
	vector<tagEffect> _acEffect;
	vector<tagEffect> _shEffect;
	vector<tagEffect> _stEffect;

	tagEffect plEffect;
	tagEffect bossEffect;
	tagEffect acEffect;
	tagEffect shEffect;
	tagEffect stEffect;

	int _cnt;
	POINT _idx[5];

public:
	HRESULT init(void);
	void addEffect(tagEffect effect, int vectorNum);
	void updateEffect(void);
	void renderEffect(HDC hdc);

	Effect() {}
	~Effect() {}
};

