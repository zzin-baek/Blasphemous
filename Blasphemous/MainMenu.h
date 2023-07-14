#pragma once
#include "GameNode.h"

class MainMenu : public GameNode
{
private:
	int cnt, idx, minus, _menuSelect;
	int idx_bg, idx_petal, idx_crisanta, idx_petal_fg;
	int idx_angel;
	POINT bg, crisanta, petal, petal_fg, angel;
	POINT _angelPos;

	COLORREF _menu1, _menu2;

	int _select;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int getSelect() { return _select; }

	MainMenu() {}
	~MainMenu() {}
};

