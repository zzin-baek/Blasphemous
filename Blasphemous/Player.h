#pragma once
#include "SingletonBase.h"

struct POINTF
{
	float x;
	float y;
};

// bitset: 기본, 걷기, 점프, 앉기, 매달리기
enum eState
{
	WALK = 0,
	JUMP,
	UP,
	ATTACK,
	CROUCH,
	CLIMB,
	LADDER,
	DODGE,
	HANGON,
	PARRY,
	HIT,
	PORTION,
	DEATH,
	DEATH_FALL,
	MAX_STATE

};

struct plImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

// bool _isGround: 바닥인지 공중인지
class Player : public SingletonBase <Player>
{
private:
	char _strAction[128];
	bitset<MAX_STATE> _plState;
	deque<char*> _actionList;
	map<string, plImageInfo> _sync;
	vector<int> _attackTime, _comboTime;
	
	RECT _player, _hitBox;
	POINTF _plPos, _center, _temp;

	bool _isLeft, _isGround, _isFixed, _isAttack;
	bool _hold, _collect, _hit, _parrying;
	bool _collected, _respawn, _press, _die;

	int _cnt, _idx_x, _idx_y, _alpha;
	int _hp, _score, _portion, _parry, _death;

	float _jumpTime, _jumpHeight, _jumpPower;

	char _loc[128], _action[128];

public:
	HRESULT init(void);
	HRESULT init(int startX, int startY);
	void initImage(void);
	void initTiming(void);
	void initSound(void);
	void playerAction(void);
	void playerMove(void);
	void comboAttack(void);
	void renderPlayer(HDC hdc);
	void renderProfile(HDC hdc);

	inline void setPosX(float x) { _plPos.x = x; }
	inline void setPosY(float y) { _plPos.y = y; }
	inline void setPosYPush(float y) { _plPos.y -= y; }
	inline float getPosX() { return _plPos.x; }
	inline float getPosY() { return _plPos.y; }

	inline void setGround(bool state) { _isGround = state; }
	inline bool getGround() { return _isGround; }
	inline bool getLeft() { return _isLeft; }
	inline void setFixed(bool state) { _isFixed = state; }
	inline bool getFixed() { return _isFixed; }
	inline void setHold(bool state) { _hold = state; }
	inline void setRespawn(bool state) { _respawn = state; }
	inline bool getRespawn() { return _respawn; }

	inline void setCollect(bool state) { _collect = state; }
	inline bool getCollected() { return _collected; }

	inline int getParry() { return _parry; }
	inline void setParry(int parry) { _parry = parry; }

	inline void setHit(bool state) { _hit = state; }
	inline bool getHit() { return _hit; }

	inline void setPress(bool state) { _press = state; }
	inline float getJumpPower() { return _jumpPower; }

	inline void setAction(char* _action) { wsprintf(_strAction, _action); }
	inline char* getAction() { return _strAction; }
	inline void addAction(char* _action) { _actionList.push_back(_action); }

	int getMaxFrameX();

	// 상태 getset
	bitset<MAX_STATE> getState() { return _plState; }
	void setState(int num, bool state) { _plState.set(num, state); }
	bool isEmpty() { return _actionList.empty(); }

	inline RECT getRect() { return _player; }
	inline RECT getHitBox() { return _hitBox; }
	inline float getCenterX() { return _center.x; }
	inline float getCenterY() { return _center.y; }

	inline bool getAttack() { return _isAttack; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	Player() {}
	~Player();
};