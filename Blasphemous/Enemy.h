#pragma once

enum tagEnemy
{
	IDLE_ENEMY = 0,
	ATTACK_ENEMY,
	HIT_ENEMY,
	DIE_ENEMY,
	MAX_ENEMY_STATE
};

struct emImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

class Enemy
{
public:
	virtual HRESULT init(void);
	virtual void initSync(void);
	virtual void move(void);
	virtual void render(HDC hdc);

	Enemy() {}
	~Enemy() {}
};

