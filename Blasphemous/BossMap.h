#pragma once

class BossMap
{
private:
	POINT _pos, _idx;
	RECT _sceneStart;

	char _brazier[128];
	int _cnt;

public:
	HRESULT init(void);
	void movdRect(int x);
	void update(void);
	void render(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	RECT getRect() { return _sceneStart; }

	BossMap() {}
	~BossMap() {}
};

