#pragma once

class BattleField
{
private:
	POINT _startPos;
	RECT _box[20];

public:
	HRESULT init(void);

	void movePlayer();
	void render(HDC hdc);

	void setX(int x) { _startPos.x = x; }
	void setY(int y) { _startPos.y = y; }
	int getX() { return _startPos.x; }
	int getY() { return _startPos.y; }

	RECT getBox(int num) { return _box[num]; }

	BattleField() {}
	~BattleField() {}
};

