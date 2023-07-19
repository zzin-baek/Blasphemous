#pragma once

class Item
{
private:
	RECT _object;
	POINT _pos, _idx;
	
	int _cnt, _obj;
	bool _pick;

public:
	HRESULT init(int _posX, int _posY);
	void update(void);
	void showItem(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	RECT getRect() { return _object; }
	void setPick(bool state) { _pick = state; }

	Item() {}
	~Item() {}
};