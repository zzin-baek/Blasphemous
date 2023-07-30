#pragma once

class BattleField
{
private:
	float _startPos_x, _startPos_y;
	float _copyPos_x, _copyPos_y;
	RECT _ladder;

public:
	HRESULT init(void);
	void rectMove(void);
	void renderDoor(HDC hdc);
	void render(HDC hdc);

	void setX(float x) { _startPos_x = x; }
	void setY(float y) { _startPos_y = y; }
	float getX() { return _startPos_x; }
	float getY() { return _startPos_y; }

	RECT getLadder() { return _ladder; }

	BattleField() {}
	~BattleField() {}
};

