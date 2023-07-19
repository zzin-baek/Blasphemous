#pragma once

class BattleField
{
private:
	float _startPos_x, _startPos_y;
	float _copyPos_x, _copyPos_y;
	RECT _grab[4];

public:
	HRESULT init(void);
	void rectMove(void);
	void render(HDC hdc);

	void setX(float x) { _startPos_x = x; }
	void setY(float y) { _startPos_y = y; }
	float getX() { return _startPos_x; }
	float getY() { return _startPos_y; }

	RECT getHold(int num) { return _grab[num]; }

	BattleField() {}
	~BattleField() {}
};

