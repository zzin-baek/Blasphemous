#pragma once

class BattleField
{
private:
	float _startPos_x, _startPos_y;
	POINT _startPos;
	RECT _grab[4];

public:
	HRESULT init(void);

	void render(HDC hdc);

	void setX(float x) { _startPos_x = x; }
	void setY(float y) { _startPos_y = y; }
	float getX() { return _startPos_x; }
	float getY() { return _startPos_y; }

	BattleField() {}
	~BattleField() {}
};

