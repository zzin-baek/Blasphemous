#pragma once
#include "SingletonBase.h"

#define MAX_STATE 11

// bitset: 기본, 걷기, 점프, 앉기, 매달리기
enum eState
{
	WALK = 0,
	JUMP,
	ATTACK,
	CROUCH,
	CLIMB,
	LADDER,
	DODGE,
	HANGON,
	PARRY,
	HIT,
	PORTION
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
	deque<string> _actionList;
	map<string, plImageInfo> _sync;
	vector<int> _attackTime, _comboTime;
	
	RECT _player;
	POINT _plPos;
	float _plPos_x, _plPos_y, _centerX, _centerY;
	bool _isLeft, _isGround, _isFixed, _hold, _collect;

	int _hitCool;
	int _cnt, _idx_x, _idx_y;
	POINT _center;
	float _tempX, _tempY;

	int _hp, _score, _portion;
	bool _collected, _respawn;

	char _loc[128], _action[128];

public:
	HRESULT init(void);
	HRESULT init(int startX, int startY);
	void initImage(void);
	void initTiming(void);
	void playerAction(void);
	void playerMove(void);
	void comboAttack(void);
	void renderPlayer(HDC hdc);
	void renderProfile(HDC hdc);

	inline void setPosX(float x) { _plPos_x = x; }
	inline void setPosY(float y) { _plPos_y = y; }

	inline float getPosX() { return _plPos_x; }
	inline float getPosY() { return _plPos_y; }

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

	inline void setAction(char* _action) { wsprintf(_strAction, _action); }
	inline void addAction(string _action) { _actionList.push_back(_action); }

	int getMaxFrameX();

	// 상태 getset
	bitset<MAX_STATE> getState() { return _plState; }
	void setState(int num, bool state) { _plState.set(num, state); }
	bool isEmpty() { return _actionList.empty(); }

	inline RECT getRect() { return _player; }
	inline float getCenterX() { return _centerX; }
	inline float getCenterY() { return _centerY; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	Player() {}
	~Player();
};