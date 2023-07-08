#pragma once
#include "GameNode.h"

class MainMenu : public GameNode
{
private:
	int cnt, idx, minus;
	int idx_bg, idx_petal, idx_crisanta, idx_petal_fg;
	POINT bg, crisanta, petal, petal_fg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainMenu() {}
	~MainMenu() {}
};

