#pragma once

class BattleField
{
private:
	POINT _startPos;
	RECT _box[2];

public:
	HRESULT init(void);

	void render(HDC hdc);

	void setX(int x) { _startPos.x = x; }
	void setY(int y) { _startPos.y = y; }
	int getX() { return _startPos.x; }
	int getY() { return _startPos.y; }

	RECT getBox(int num) { return _box[num]; }
	void setBox(int num, int x, int y) {
		_box[num].left += x; _box[num].right += x;
		_box[num].top += y; _box[num].bottom += y;
	}
	int getBoxSize() { return sizeof(_box) / sizeof(RECT); }

	BattleField() {}
	~BattleField() {}
};

