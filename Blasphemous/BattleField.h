#pragma once

class BattleField
{
private:
	float _startPos_x, _startPos_y;
	float _copyPos_x, _copyPos_y;
	POINTF _shake;
	RECT _ladder;

public:
	HRESULT init(void);
	void rectMove(void);
	void cameraShake(void);
	void renderDoor(HDC hdc);
	void render(HDC hdc);

	void setX(float x) { _startPos_x = x; }
	void setY(float y) { _startPos_y = y; }
	float getX() { return _startPos_x; }
	float getY() { return _startPos_y; }

	void initCamera() { _shake = { 0, 0 }; }

	RECT getLadder() { return _ladder; }

	BattleField() {}
	~BattleField() {}
};

