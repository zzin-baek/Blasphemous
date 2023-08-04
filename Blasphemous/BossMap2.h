#pragma once

class BossMap2
{
private:
	POINT _pos, _idx;

public:
	HRESULT init(void);
	void render(HDC hdc);
	void renderColumn(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	BossMap2() {}
	~BossMap2() {}
};

