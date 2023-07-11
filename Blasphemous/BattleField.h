#pragma once

class BattleField
{
private:
	float _startPos_x, _startPos_y;
	RECT _box[4];
	RECT _grab[4];

public:
	HRESULT init(void);

	void render(HDC hdc);

	void setX(int x) { _startPos_x = x; }
	void setY(int y) { _startPos_y = y; }
	int getX() { return _startPos_x; }
	int getY() { return _startPos_y; }

	RECT getBox(int num) { return _box[num]; }
	void setBox(int num, int x, int y) {
		_box[num].left += x; _box[num].right += x;
		_box[num].top += y; _box[num].bottom += y;
	}
	int getBoxSize() { return sizeof(_box) / sizeof(RECT); }

	BattleField() {}
	~BattleField() {}
};

