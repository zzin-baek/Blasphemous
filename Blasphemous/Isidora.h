#pragma once
class Isidora
{
private:
	POINT _pos;
	int _cnt, _idx;
	int _idx_x, _idx_y;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);

	inline int getX() { return _pos.x; }
	inline int getY() { return _pos.y; }
	inline void setX(int x) { _pos.x = x; }
	inline void setY(int y) { _pos.y = y; }

	Isidora() {}
	~Isidora() {}
};

