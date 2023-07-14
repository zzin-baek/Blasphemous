#pragma once

enum tagEnemy
{
	IDLE_ENEMY = 0,
	ATTACK_EMEMY,
	HIT_ENEMY
};

class Enemy
{
public:
	HRESULT init(void);
	void move(void);
	void render(HDC hdc);

	Enemy() {}
	~Enemy() {}
};

