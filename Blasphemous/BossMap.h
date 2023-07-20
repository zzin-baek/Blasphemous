#pragma once

class BossMap
{
private:
	POINT _pos;
	RECT _sceneStart;

public:
	HRESULT init(void);
	void movdRect(int x);
	void render(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	RECT getRect() { return _sceneStart; }

	BossMap() {}
	~BossMap() {}
};

