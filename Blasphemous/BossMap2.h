#pragma once

class BossMap2
{
private:
	POINT _pos, _idx;
	RECT _sceneStart;
	int _cnt, _ind;

public:
	HRESULT init(void);
	void moveRect(int x);
	void render(HDC hdc);
	void update(void);
	void renderColumn(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	RECT getRect() { return _sceneStart; }

	BossMap2() {}
	~BossMap2() {}
};
