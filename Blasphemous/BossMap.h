#pragma once

class BossMap
{
private:
	POINT _pos, _idx;
	RECT _sceneStart;

	char _brazier[128];
	int _cnt, _scene;

public:
	HRESULT init(void);
	void moveRect(int x);
	void update(void);
	void render(HDC hdc);

	inline void setPosX(int x) { _pos.x = x; }
	inline void setPosY(int y) { _pos.y = y; }
	inline int getPosX() { return _pos.x; }
	inline int getPosY() { return _pos.y; }

	inline void setScene(int scene) { _scene = scene; }
	inline int getScene() { return _scene; }

	RECT getRect() { return _sceneStart; }
	void changeBrazier(char* brazier) { wsprintf(_brazier, brazier); }

	BossMap() {}
	~BossMap() {}
};