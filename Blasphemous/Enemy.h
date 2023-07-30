#pragma once

enum tagEnemy
{
	IDLE_ENEMY = 0,
	ATTACK_ENEMY,
	HIT_ENEMY,
	DIE_ENEMY
};

class Enemy
{
public:
	virtual HRESULT init(void);
	virtual void move(void);
	virtual void render(HDC hdc);

	Enemy() {}
	~Enemy() {}
};

