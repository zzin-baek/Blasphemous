#pragma once

class BossMap
{
private:
	POINT _pos;

public:
	HRESULT init(void);
	void render(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	BossMap() {}
	~BossMap() {}
};

